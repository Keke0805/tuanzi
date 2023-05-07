#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
using namespace std;

template<typename tParam>
class SlotBase
{
public:
    virtual void Exec(tParam param) = 0;
};

template<class T, class tParam>
class SlotImpl : public SlotBase<tParam>
{
public:
    SlotImpl(T* pObj, void (T::* func)(tParam))
    {
        m_pObj = pObj;
        m_Func = func;
    }

    void Exec(tParam param)
    {
        (m_pObj->*m_Func)(param);
    }

private:
    T* m_pObj;
    void (T::* m_Func)(tParam);
};

template<class tParam>
class Slot
{
public:
    template<class T>
    Slot(T* pObj, void (T::* func)(tParam))
    {
        m_pSlotBase = new SlotImpl<T, tParam>(pObj, func);
    }

    ~Slot()
    {
        delete m_pSlotBase;
    }

    void Exec(tParam param1)
    {
        m_pSlotBase->Exec(param1);
    }

private:
    SlotBase<tParam>* m_pSlotBase;
};

template<typename tParam>
class Signal
{
public:
    template<class T>
    void Bind(T* pObj, void (T::* func)(tParam))
    {
        m_pSlotSet.push_back(new Slot<tParam>(pObj, func));
    }

    ~Signal()
    {
        for (int i = 0; i < (int)m_pSlotSet.size(); i++)
        {
            delete m_pSlotSet[i];
        }
    }

    void operator()(tParam param1)
    {
        for (int i = 0; i < (int)m_pSlotSet.size(); i++)
        {
            m_pSlotSet[i]->Exec(param1);
        }
    }

private:
    vector< Slot<tParam>* > m_pSlotSet;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... Args>
class Slot_M
{
public:
    using OnFunc = std::function<void(Args&&...)>;

    Slot_M(const OnFunc& func) : m_func(func)
    {
        // Do nothing
    }

    ~Slot_M()
    {
        if (m_func != NULL)
        {
            delete m_func;
        }
    }

    void exec(Args&&... args)
    {
        m_func(std::forward<Args>(args)...);
    }

private:
    OnFunc m_func = nullptr;
};

template<typename... Args>
class Signal_M
{
public:
    using SlotPtr = std::shared_ptr<Slot_M<Args&&...>>;
    using OnFunc = std::function<void(Args&&...)>;

    void Bind(const OnFunc& func)
    {
        m_slotVec.push_back(SlotPtr(new Slot_M<Args&&...>(func)));
    }

    ~Signal_M()
    {
        delete m_slotVec;
    }

    void operator()(Args&&... args)
    {
        for (auto& iter : m_slotVec)
        {
            iter->exec(std::forward<Args>(args)...);
        }
    }

private:
    std::vector<SlotPtr> m_slotVec;
};

#define THROUGH_BRIDGE_S(signal, receiver, method) (signal.Bind(receiver, method))
#define THROUGH_BRIDGE_M(signal_m, slot_m) (signal_m.Bind(slot_m))


// 1. THROUGH_BRIDGE_S(gui_parament_tree->sendmsg_to_main,this, &MainWindow::callback_from_collapse);
// 2. THROUGH_BRIDGE_M(gui_parament_tree->sendmsg_to_main, std::bind(&MainWindow::func1, this));  // para num: none
// 3. THROUGH_BRIDGE_M(gui_parament_tree->sendmsg_to_main, std::bind(&MainWindow::func2, this, std::placeholders::_1)); // para num: 1
// 4. THROUGH_BRIDGE_M(gui_parament_tree->sendmsg_to_main, std::bind(&MainWindow::func3, this, std::placeholders::_1, std::placeholders::_2));  // para num: 2
