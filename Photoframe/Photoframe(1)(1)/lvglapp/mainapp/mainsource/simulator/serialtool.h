#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

#if QTSIM_PLATFORM

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


#define RECV_MAX_SIZE  1024

typedef std::function<void(QByteArray)> SerialCallBack;

//串口工具类
class SerialTool: public QSerialPort
{
    Q_OBJECT
public:
    SerialTool(lv_obj_t* parent = nullptr);
    ~SerialTool();

    void initial(void);
    void refresh(void);

    int Connect(void);
    int Disconnect(void);

    void tool_setPortname(int index);
    void tool_setBaudRate(int index);
    void tool_setDataBits(int index);
    void tool_setParity(int index);
    void tool_setStopBits(int index);
    void tool_setFlowControl(int index); //设置为无流控制

    void ReadData(void);
    void SendData(const char *data);

    void SetRecvCallback(SerialCallBack func);

signals:
    void button_send();
    void recv_send();

protected:


private:
    int app_initial(void);

    LvcppScreen* main_screen=nullptr;
    lv_obj_t* m_panel=nullptr;

    SerialCallBack Recvdata;
    QSerialPort* m_serial;
    QList<QSerialPortInfo> allports;
    int serial_link;

    QString  ser_name;
    int  ser_baudrate;
    QSerialPort::DataBits ser_dataBits;
    QSerialPort::Parity ser_parity;
    QSerialPort::StopBits  ser_stopbits;
    QSerialPort::FlowControl  ser_flowctl;

    LvcppLabel* port_num=nullptr;
    LvcppDropdown* port_num_sel=nullptr;

    LvcppLabel* port_baud=nullptr;
    LvcppDropdown* port_baud_sel=nullptr;

    LvcppLabel* port_databit=nullptr;
    LvcppDropdown* port_databit_sel=nullptr;

    LvcppLabel* port_parity=nullptr;
    LvcppDropdown* port_parity_sel=nullptr;

    LvcppLabel* port_stopbit=nullptr;
    LvcppDropdown* port_stopbit_sel=nullptr;

    LvcppLabel* port_flowcontrol=nullptr;
    LvcppDropdown* port_flowcontrol_sel=nullptr;

    LvcppButton* btn_connect=nullptr;
    LvcppLabel* connect_status=nullptr;

    LvcppButton* btn_cancel=nullptr;

    static void dropdown_event_handler(lv_event_t* event);
    static void connect_event_handler(lv_event_t* event);
    static void close_event_handler(lv_event_t* event);

    void select_disable(void);
    void select_enable(void);
};

#endif

#endif // SERIALTOOL_H
