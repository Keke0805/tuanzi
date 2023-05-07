#include "serialtool.h"

#if QTSIM_PLATFORM

const char* mBaudRate ={
    "1200\n"
    "2400\n"
    "4800\n"
    "9600\n"
    "19200\n"
    "38400\n"
    "57600\n"
    "115200"
};


const char* mDataBits ={
    "5\n"
    "6\n"
    "7\n"
    "8"
};

const char* mParity ={
    "None\n"
    "Even\n"
    "Odd\n"
    "Space\n"
    "Mark"
};

const char* mStopBits ={
    "1\n"
    "1.5\n"
    "2"
};

const char* mFlowControl ={
    "None\n"
    "Hardware\n"
    "Software\n"
    "Custom"
};


SerialTool::SerialTool(lv_obj_t* parent)
{
    main_screen = new LvcppScreen(parent);
    main_screen->set_size(280,300);//MONITOR_HOR_RES:MONITOR_VER_RES
    main_screen->center_align();
    main_screen->set_scrollbar_mode(0);
    main_screen->set_main_border_width(5);
    main_screen->set_main_shadow_width(5);
    main_screen->set_main_bg_color(lv_color_hex(0xFFE0E0E0), LV_OPA_COVER);
    m_panel = main_screen->myobj;

    m_serial = new QSerialPort();
    app_initial();
    initial();
    serial_link = 0;
}

SerialTool::~SerialTool()
{
    if(m_serial!=nullptr)
    {
        delete m_serial;
        m_serial = NULL;
    }

    delete btn_cancel;
    btn_cancel = NULL;

    delete connect_status;
    connect_status = NULL;

    delete btn_connect;
    btn_connect = NULL;

    delete port_num;
    port_num = NULL;

    delete port_num_sel;
    port_num_sel = NULL;

    delete port_baud;
    port_baud = NULL;

    delete port_baud_sel;
    port_baud_sel = NULL;

    delete port_databit;
    port_databit = NULL;

    delete port_databit_sel;
    port_databit_sel = NULL;

    delete port_parity;
    port_parity = NULL;

    delete port_parity_sel;
    port_parity_sel = NULL;

    delete port_stopbit;
    port_stopbit = NULL;

    delete port_stopbit_sel;
    port_stopbit_sel = NULL;

    delete port_flowcontrol;
    port_flowcontrol = NULL;

    delete port_flowcontrol_sel;
    port_flowcontrol_sel = NULL;

    delete  main_screen;
    main_screen = NULL;
}

int SerialTool::app_initial(void)
{
    //端口号
    port_num = new LvcppLabel(m_panel);
    port_num->set_size(90,30);
    port_num->set_pos(5,5);
    port_num->set_main_pad_all(0);
    port_num->set_scrollbar_mode(0);
    port_num->txt_color(lv_color_hex(0x000000),0);
    port_num->set_txt("端口号:");
    port_num->txt_font_size(24,0);
    port_num->txt_align(LV_ALIGN_RIGHT_MID);
    port_num->set_main_border_width(0);

    port_num_sel = new LvcppDropdown(m_panel);
    port_num_sel->set_size(165,35);
    port_num_sel->set_main_pad_T_B(3,3);
    port_num_sel->set_scrollbar_mode(0);
    port_num_sel->align_to(port_num->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-2);
    port_num_sel->add_event_cb(dropdown_event_handler,LV_EVENT_CLICKED,this);
    port_num_sel->add_event_cb(dropdown_event_handler,LV_EVENT_VALUE_CHANGED,this);

    //波特率
    port_baud = new LvcppLabel(m_panel);
    port_baud->set_size(90,30);
    port_baud->align_to(port_num->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
    port_baud->set_scrollbar_mode(0);
    port_baud->set_main_pad_all(0);
    port_baud->txt_color(lv_color_hex(0x000000),0);
    port_baud->set_txt("波特率:");
    port_baud->txt_font_size(24,0);
    port_baud->txt_align(LV_ALIGN_RIGHT_MID);
    port_baud->set_main_border_width(0);

    port_baud_sel = new LvcppDropdown(m_panel);
    port_baud_sel->set_size(165,35);
    port_baud_sel->set_main_pad_T_B(3,3);
    port_baud_sel->set_scrollbar_mode(0);
    port_baud_sel->align_to(port_baud->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-2);
    port_baud_sel->set_options(mBaudRate);
    port_baud_sel->add_event_cb(dropdown_event_handler,LV_EVENT_CLICKED,this);
    port_baud_sel->add_event_cb(dropdown_event_handler,LV_EVENT_VALUE_CHANGED,this);

    //数据位
    port_databit = new LvcppLabel(m_panel);
    port_databit->set_size(90,30);
    port_databit->align_to(port_baud->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
    port_databit->set_main_pad_all(0);
    port_databit->set_scrollbar_mode(0);
    port_databit->txt_color(lv_color_hex(0x000000),0);
    port_databit->set_txt("数据位:");
    port_databit->txt_font_size(24,0);
    port_databit->txt_align(LV_ALIGN_RIGHT_MID);
    port_databit->set_main_border_width(0);

    port_databit_sel = new LvcppDropdown(m_panel);
    port_databit_sel->set_size(165,35);
    port_databit_sel->set_main_pad_T_B(3,3);
    port_databit_sel->set_scrollbar_mode(0);
    port_databit_sel->align_to(port_databit->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-2);
    port_databit_sel->set_options(mDataBits);
    port_databit_sel->add_event_cb(dropdown_event_handler,LV_EVENT_VALUE_CHANGED,this);

    //校验位
    port_parity = new LvcppLabel(m_panel);
    port_parity->set_size(90,30);
    port_parity->align_to(port_databit->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
    port_parity->set_main_pad_all(0);
    port_parity->set_scrollbar_mode(0);
    port_parity->txt_color(lv_color_hex(0x000000),0);
    port_parity->set_txt("校验位:");
    port_parity->txt_font_size(24,0);
    port_parity->txt_align(LV_ALIGN_RIGHT_MID);
    port_parity->set_main_border_width(0);

    port_parity_sel = new LvcppDropdown(m_panel);
    port_parity_sel->set_size(165,35);
    port_parity_sel->set_main_pad_T_B(3,3);
    port_parity_sel->set_scrollbar_mode(0);
    port_parity_sel->align_to(port_parity->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-2);
    port_parity_sel->set_options(mParity);
    port_parity_sel->add_event_cb(dropdown_event_handler,LV_EVENT_VALUE_CHANGED,this);


    //停止位
    port_stopbit = new LvcppLabel(m_panel);
    port_stopbit->set_size(90,30);
    port_stopbit->align_to(port_parity->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
    port_stopbit->set_main_pad_all(0);
    port_stopbit->set_scrollbar_mode(0);
    port_stopbit->txt_color(lv_color_hex(0x000000),0);
    port_stopbit->set_txt("停止位:");
    port_stopbit->txt_font_size(24,0);
    port_stopbit->txt_align(LV_ALIGN_RIGHT_MID);
    port_stopbit->set_main_border_width(0);

    port_stopbit_sel = new LvcppDropdown(m_panel);
    port_stopbit_sel->set_size(165,35);
    port_stopbit_sel->set_main_pad_T_B(3,3);
    port_stopbit_sel->set_scrollbar_mode(0);
    port_stopbit_sel->align_to(port_stopbit->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-2);
    port_stopbit_sel->set_options(mStopBits);
    port_stopbit_sel->add_event_cb(dropdown_event_handler,LV_EVENT_VALUE_CHANGED,this);

    //流控制
    port_flowcontrol = new LvcppLabel(m_panel);
    port_flowcontrol->set_size(90,30);
    port_flowcontrol->align_to(port_stopbit->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
    port_flowcontrol->set_main_pad_all(0);
    port_flowcontrol->set_scrollbar_mode(0);
    port_flowcontrol->txt_color(lv_color_hex(0x000000),0);
    port_flowcontrol->set_txt("流控制:");
    port_flowcontrol->txt_font_size(24,0);
    port_flowcontrol->txt_align(LV_ALIGN_RIGHT_MID);
    port_flowcontrol->set_main_border_width(0);

    port_flowcontrol_sel = new LvcppDropdown(m_panel);
    port_flowcontrol_sel->set_size(165,35);
    port_flowcontrol_sel->set_main_pad_T_B(3,3);
    port_flowcontrol_sel->set_scrollbar_mode(0);
    port_flowcontrol_sel->align_to(port_flowcontrol->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-2);
    port_flowcontrol_sel->set_options(mFlowControl);
    port_flowcontrol_sel->add_event_cb(dropdown_event_handler,LV_EVENT_VALUE_CHANGED,this);

    btn_connect = new LvcppButton(m_panel);
    btn_connect->set_size(90,35);
    btn_connect->set_scrollbar_mode(0);
    btn_connect->set_main_pad_all(0);
    btn_connect->set_main_bg_color(lv_color_hex(0x00aa99),LV_OPA_70);
    btn_connect->set_main_border_width(5);
    btn_connect->set_main_border_color(lv_color_hex(0xffff5599));
    btn_connect->align_to(port_flowcontrol->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,30,10);
    btn_connect->add_txt("连接");
    btn_connect->txt_font_size(24,0);
    btn_connect->txt_center();
    btn_connect->add_event_cb(connect_event_handler,LV_EVENT_CLICKED,this);

    btn_cancel = new LvcppButton(m_panel);
    btn_cancel->set_size(90,35);
    btn_cancel->set_scrollbar_mode(0);
    btn_cancel->set_main_pad_all(0);
    btn_cancel->set_main_bg_color(lv_color_hex(0xaabbcc),LV_OPA_100);
    btn_cancel->set_main_border_width(2);
    btn_cancel->set_main_border_color(lv_color_hex(0x000000));
    btn_cancel->align_to(btn_connect->myobj,LV_ALIGN_OUT_RIGHT_TOP,30,0);
    btn_cancel->add_txt("关闭");
    btn_cancel->txt_font_size(24,0);
    btn_cancel->txt_center();
    btn_cancel->add_event_cb(close_event_handler,LV_EVENT_CLICKED,this);

    connect_status = new LvcppLabel(m_panel);
    connect_status->set_size(200,30);
    connect_status->align_to(btn_connect->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,10,5);
    connect_status->set_main_pad_all(0);
    connect_status->set_scrollbar_mode(0);
    connect_status->txt_color(lv_color_hex(0xff0000),0);
    connect_status->set_txt("串口未连接");
    connect_status->txt_align(LV_TEXT_ALIGN_CENTER);
    connect_status->txt_font_size(20,0);
    connect_status->set_main_border_width(0);
    return 0;
}

void SerialTool::dropdown_event_handler(lv_event_t* event)
{
    SerialTool* opt = (SerialTool*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(target == opt->port_num_sel->myobj)
        {
            opt->tool_setPortname(opt->port_num_sel->get_selected());
        }
        else if(target == opt->port_baud_sel->myobj)
        {
            opt->tool_setBaudRate(opt->port_baud_sel->get_selected());
        }
        else if(target == opt->port_databit_sel->myobj)
        {
            opt->tool_setDataBits(opt->port_databit_sel->get_selected());
        }
        else if(target == opt->port_parity_sel->myobj)
        {
            opt->tool_setParity(opt->port_parity_sel->get_selected());
        }
        else if(target == opt->port_stopbit_sel->myobj)
        {
            opt->tool_setStopBits(opt->port_stopbit_sel->get_selected());
        }
        else if(target == opt->port_flowcontrol_sel->myobj)
        {
            opt->tool_setFlowControl(opt->port_flowcontrol_sel->get_selected());
        }
    }
    else if(code == LV_EVENT_CLICKED)
    {
        QString str = opt->port_num_sel->get_options();
        qDebug("%s---",qPrintable(str));
        if(target == opt->port_num_sel->myobj)
        {
            opt->refresh();
        }
    }
}

void SerialTool::connect_event_handler(lv_event_t* event)
{
    SerialTool* opt = (SerialTool*) event->user_data;
    if(opt->serial_link == 0)
    {
       opt->Connect();
    }
    else
    {
       opt->Disconnect();
    }
}

void SerialTool::close_event_handler(lv_event_t* event)
{
    SerialTool* opt = (SerialTool*) event->user_data;

    opt->main_screen->show(false);
    opt->button_send();//send signal to sim
}

void SerialTool::initial(void)
{
    int port_cnt=0;
    port_num_sel->clear_options();

    allports = QSerialPortInfo::availablePorts();
    for (int i = 0; i < allports.size();i++)
    {
        for (int j = i + 1; j < allports.size(); j++)
        {
            QString name = allports.at(i).portName();
            int portNumI = name.mid(3).toInt();

            name = allports.at(j).portName();
            int portNumJ = name.mid(3).toInt();

            if (portNumI > portNumJ)
            {
                allports.swapItemsAt(i, j);
            }
        }
    }

    foreach (const QSerialPortInfo &info, allports)
    {
        m_serial->setPort(info);
        std::string str = info.portName().toStdString();
        port_num_sel->add_option(str.c_str(),port_cnt);
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
        qDebug() << "System Location: " << info.systemLocation();
        m_serial->close();
        port_cnt++;
    }

    //默认串口参数
    port_num_sel->set_selected(0);
    tool_setPortname(0);

    port_baud_sel->set_selected(7);
    tool_setBaudRate(7);

    port_databit_sel->set_selected(3);
    tool_setDataBits(3);

    port_parity_sel->set_selected(0);
    tool_setParity(0);

    port_stopbit_sel->set_selected(0);
    tool_setStopBits(0);

    port_flowcontrol_sel->set_selected(0);
    tool_setFlowControl(0);

    qDebug("inition serial end------");
}

void SerialTool::refresh(void)
{
    int port_cnt=0;
    char buf[16];
    port_num_sel->get_selected_str(buf,16);
    port_num_sel->clear_options();

    allports = QSerialPortInfo::availablePorts();
    for (int i = 0; i < allports.size();i++)
    {
        for (int j = i + 1; j < allports.size(); j++)
        {
            QString name = allports.at(i).portName();
            int portNumI = name.mid(3).toInt();

            name = allports.at(j).portName();
            int portNumJ = name.mid(3).toInt();

            if (portNumI > portNumJ)
            {
                allports.swapItemsAt(i, j);
            }
        }
    }

    foreach (const QSerialPortInfo &info, allports)
    {
        m_serial->setPort(info);
        std::string str = info.portName().toStdString();
        port_num_sel->add_option(str.c_str(),port_cnt);
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
        qDebug() << "System Location: " << info.systemLocation();

        m_serial->close();
        port_cnt++;
    }

    port_num_sel->set_selected(0);
    tool_setPortname(0);
}

int SerialTool::Connect()
{
    m_serial->setPortName(ser_name);  //设置端口号
    m_serial->setBaudRate(ser_baudrate);  //设置波特率
    m_serial->setDataBits(ser_dataBits);				//数据位
    m_serial->setParity(ser_parity);				//校验位
    m_serial->setStopBits(ser_stopbits);			//停止位
    m_serial->setFlowControl(ser_flowctl);	//设置流控制

    qDebug().quote() << ser_name << ser_baudrate << ser_dataBits << ser_parity << ser_stopbits << ser_flowctl;

    if(m_serial->isOpen())
    {
        qDebug() << "提示:" << "串口已连接，请先断开连接设备";
        return 0;
    }

    if (!m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "提示:" << "串口连接失败,请检查设备是否正确连接";
        connect_status->set_txt("串口打开失败");
        return 0;
    }
    else
    {
        qDebug() << "提示:" << ser_name << "连接成功";
        m_serial->setDataTerminalReady(true);

        //bind senddata
        connect(m_serial, &QSerialPort::readyRead , this, &SerialTool::ReadData);

        m_serial->clearError();
        m_serial->clear();

        QString  outstr;
        outstr.sprintf("%s 端口已连接成功",ser_name.toStdString().c_str());
        connect_status->set_txt(outstr.toStdString().c_str());
        connect_status->txt_color(lv_color_hex(0x0055ff),0);

        btn_connect->add_txt("断开");
        btn_connect->set_main_bg_color(lv_color_hex(0xff0000),LV_OPA_COVER);
        select_disable();
        serial_link = 1;
    }

    return 1;
}

int SerialTool::Disconnect(void)
{
    if(m_serial->isOpen())
    {
        m_serial->close();
        qDebug() << "提示:" << "串口连接断开！";

        QString  outstr;
        outstr.sprintf("%s 串口连接断开！",ser_name.toStdString().c_str());
        connect_status->set_txt(outstr.toStdString().c_str());
        connect_status->txt_color(lv_color_hex(0xff0000),0);

        btn_connect->add_txt("连接");
        btn_connect->set_main_bg_color(lv_color_hex(0x00aa99),LV_OPA_COVER);

        select_enable();
        serial_link = 0;
    }

    return 0;
}

void SerialTool::tool_setPortname(int index)
{
    if((index + 1) > allports.size())
    {
        ser_name = "";
    }
    else
    {
        ser_name = allports.at(index).portName();
    }
}
void SerialTool::tool_setBaudRate(int index)
{
    if(index == 0)
    {
        ser_baudrate = 1200;
    }
    else if(index == 1)
    {
        ser_baudrate = 2400;
    }
    else if(index == 2)
    {
        ser_baudrate = 4800;
    }
    else if(index == 3)
    {
        ser_baudrate = 9600;
    }
    else if(index == 4)
    {
        ser_baudrate = 19200;
    }
    else if(index == 5)
    {
        ser_baudrate = 38400;
    }
    else if(index == 6)
    {
        ser_baudrate = 57600;
    }
    else if(index == 7)
    {
        ser_baudrate = 115200;
    }
}

void SerialTool::tool_setDataBits(int index)
{
    if(index == 0)
    {
        ser_dataBits = QSerialPort::Data5;
    }
    else if(index == 1)
    {
        ser_dataBits = QSerialPort::Data6;
    }
    else if(index == 2)
    {
        ser_dataBits = QSerialPort::Data7;
    }
    else if(index == 3)
    {
        ser_dataBits = QSerialPort::Data8;
    }
}

void SerialTool::tool_setParity(int index)
{
    if(index == 0)
    {
        ser_parity = QSerialPort::NoParity;
    }
    else if(index == 1)
    {
        ser_parity = QSerialPort::EvenParity;
    }
    else if(index == 2)
    {
        ser_parity = QSerialPort::OddParity;
    }
    else if(index == 3)
    {
        ser_parity = QSerialPort::SpaceParity;
    }
    else if(index == 4)
    {
        ser_parity = QSerialPort::MarkParity;
    }
    else if(index == 5)
    {
        ser_parity = QSerialPort::UnknownParity;
    }
}

void SerialTool::tool_setStopBits(int index)
{
    if(index == 0)
    {
        ser_stopbits = QSerialPort::OneStop;
    }
    else if(index == 1)
    {
        ser_stopbits = QSerialPort::OneAndHalfStop;
    }
    else if(index == 2)
    {
        ser_stopbits = QSerialPort::TwoStop;
    }
    else if(index == 3)
    {
        ser_stopbits = QSerialPort::UnknownStopBits;
    }
}

void SerialTool::tool_setFlowControl(int index)
{
    if(index == 0)
    {
        ser_flowctl = QSerialPort::NoFlowControl;
    }
    else if(index == 1)
    {
        ser_flowctl = QSerialPort::HardwareControl;
    }
    else if(index == 2)
    {
        ser_flowctl = QSerialPort::SoftwareControl;
    }
    else if(index == 3)
    {
        ser_flowctl = QSerialPort::UnknownFlowControl;
    }
}


void SerialTool::ReadData(void)
{
    qDebug() << "提示:" << "开始接收数据！";
    QByteArray receiveDate;
    receiveDate.clear();

    receiveDate = m_serial->readAll();
    if (!receiveDate.isEmpty())
    {
        qDebug() << "receiveDate:" << receiveDate.toHex() << "/ recv length:" << receiveDate.size();
        if(Recvdata != NULL)
        {
           Recvdata(receiveDate);
        }
        else
        {
            qDebug() << "Recvdata func is NULL";
        }
    }
    else
    {
        qDebug() << "receiveDate is NULL";
    }

    receiveDate.clear();
}

void SerialTool::SendData(const char *data)
{
    if(m_serial->isWritable())
    {
        int datalength = m_serial->write(data);
        qDebug() << "sendDate:" << data << "/ send length:" <<datalength;
    }
    else{
        qDebug() << "提示:" << "串口未打开！";
    }
}

void SerialTool::SetRecvCallback(SerialCallBack func)
{
    Recvdata = func;
}

void SerialTool::select_disable(void)
{
    port_num_sel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    port_baud_sel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    port_databit_sel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    port_parity_sel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    port_stopbit_sel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    port_flowcontrol_sel->clear_flag(LV_OBJ_FLAG_CLICKABLE);

    port_num->txt_color(lv_palette_darken(LV_PALETTE_GREY, 2), LV_PART_MAIN);
    port_baud->txt_color(lv_palette_darken(LV_PALETTE_GREY, 2), LV_PART_MAIN);
    port_databit->txt_color(lv_palette_darken(LV_PALETTE_GREY, 2), LV_PART_MAIN);
    port_parity->txt_color(lv_palette_darken(LV_PALETTE_GREY, 2), LV_PART_MAIN);
    port_stopbit->txt_color(lv_palette_darken(LV_PALETTE_GREY, 2), LV_PART_MAIN);
    port_flowcontrol->txt_color(lv_palette_darken(LV_PALETTE_GREY, 2), LV_PART_MAIN);
}

void SerialTool::select_enable(void)
{
    port_num_sel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    port_baud_sel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    port_databit_sel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    port_parity_sel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    port_stopbit_sel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    port_flowcontrol_sel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    port_num->txt_color(lv_color_black(), LV_PART_MAIN);
    port_baud->txt_color(lv_color_black(), LV_PART_MAIN);
    port_databit->txt_color(lv_color_black(), LV_PART_MAIN);
    port_parity->txt_color(lv_color_black(), LV_PART_MAIN);
    port_stopbit->txt_color(lv_color_black(), LV_PART_MAIN);
    port_flowcontrol->txt_color(lv_color_black(), LV_PART_MAIN);
}

#endif
