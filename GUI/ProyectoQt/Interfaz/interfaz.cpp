#include <QDebug>
#include <QSettings>
#include <QValidator>
#include <QMessageBox>
#include <QByteArray>
#include "interfaz.h"
#include "ui_interfaz.h"

extern double pitch;
extern double roll;
extern double yaw;
extern double out;
extern QByteArray bufferCircular;
extern int index;
#define PITCH 0
#define ROLL 1
#define YAW 2

#define LIMITE 55



Interfaz::Interfaz(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interfaz)
    {
        //Inicialización
        ui->setupUi(this);
        setpointRoll = 0;
        setpointPitch = 0;
        setpointYaw = 0;
        ui->roll2->setValue(setpointRoll);
        ui->pitch1->setValue(setpointPitch);
        for(int i = 0; i < BUFFERSIZE; i++) bufferRx[i] = ' ';
        //Inicialización de la comunicación
        Port = nullptr;    //indica que el objeto puerto no esta creado;
        Portname = "";
        EnumerarPuertos();
        HabilitarBotones(false);

        bufferCircular.resize(100);
        index = 0;
        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
        connect(&Timer, SIGNAL(timeout()), this, SLOT(verificarTrama()));
        Timer.start(10); // Interval 0 means to refresh as fast as possible


    }

Interfaz::~Interfaz()
{
    delete Port;
    delete ui;
}

void Interfaz::on_noseup_clicked()
{
    //Cosas de la interfaz - Mateo
    if(setpointPitch <= LIMITE)
    {
        setpointPitch = setpointPitch + 5;

    }else
    {
        setpointPitch = (LIMITE+5);
    }
    ui->pitch1->setValue(setpointPitch);
    //Cosas de la comunicacion

    QByteArray dato;
    dato.append(setpointPitch+128);
    GenerarTrama(&dato , 0);
    EnviarDatos(dato);


}

void Interfaz::on_nosedown_clicked()
{
    //Cosas de la interfaz - Mateo
    if(setpointPitch >= -LIMITE)
    {
        setpointPitch = setpointPitch - 5;

    }else
    {
        setpointPitch = -(LIMITE+5);
    }

    ui->pitch1->setValue(setpointPitch);
    //Cosas de la comunicacion
    QByteArray dato;
    dato.append(setpointPitch+128);
    GenerarTrama(&dato , 0);
    EnviarDatos(dato);
}

void Interfaz::on_noseright_clicked()
{
    //Cosas de la interfaz - Mateo
    if(setpointRoll <= LIMITE)
    {
        setpointRoll = setpointRoll + 5;

    }
    ui->roll2->setValue(setpointRoll);
    //Cosas de la comunicacion

    QByteArray dato;
    dato.append(setpointRoll+128);
    GenerarTrama(&dato , 1);
    EnviarDatos(dato);
}

void Interfaz::on_noseleft_clicked()
{
    //Cosas de la interfaz - Mateo
    if(setpointRoll >= -LIMITE)
    {
        setpointRoll = setpointRoll - 5;
        ui->roll2->setValue(setpointRoll);
    }
    ui->roll2->setValue(setpointRoll);
    //Cosas de la comunicacion

    QByteArray dato;
    dato.append(setpointRoll+128);
    GenerarTrama(&dato , 1);
    EnviarDatos(dato);
}

void Interfaz::on_modo1_clicked()
{

}

void Interfaz::on_modo2_clicked()
{

}

void Interfaz::on_calibrar_clicked()
{
    //Cosas de la interfaz - Mateo
    setpointPitch=0;
    setpointRoll=0;
    setpointYaw=0;
    ui->yaw->setValue(0);
    ui->roll2->setValue(0);//reseteo los valores a 0 cuando se aprieta calibrar
    ui->pitch1->setValue(0);

    //Cosas de la comunicacion
    QByteArray dato;

    //Lo pongo en modo calibracion
    dato.clear();
    GenerarTrama(&dato,3);
    EnviarDatos(dato);

    //Actualizo los datos
    dato.clear();
    dato.append(setpointPitch+128);
    GenerarTrama(&dato,0);
    EnviarDatos(dato);

    dato.clear();
    dato.append(setpointRoll+128);
    GenerarTrama(&dato,1);
    EnviarDatos(dato);

    dato.clear();
    dato.append(setpointYaw+128);
    GenerarTrama(&dato,2);
    EnviarDatos(dato);


}

void Interfaz::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();  //me devuelve una lista con los puertos que tengo

    if(ports.size() == 0)
    {
        QMessageBox::critical(this,"Error","No hay puertos disponibles!");
        //HabilitarBotones(false);

    }else{
        for (int i = 0; i < ports.size(); i++)
        {
            ui->comboBoxPort->addItem(ports.at(i).portName(), ports.at(i).portName());
        }
    }
}

void Interfaz::HabilitarBotones(bool info)
{
    ui->noseup->setEnabled(info);
    ui->nosedown->setEnabled(info);
    ui->noseleft->setEnabled(info);
    ui->noseright->setEnabled(info);
    ui->calibrar->setEnabled(info);
    ui->yaw->setEnabled(info);
    ui->pitch1->setEnabled(info);
    ui->roll2->setEnabled(info);
    ui->modo1->setEnabled(info);
    ui->modo2->setEnabled(info);
    ui->btnEnviar->setEnabled(info);
    ui->btnPlot->setEnabled(info);
}

void Interfaz::on_pitch1_editingFinished()
{
    //Cosas de la interfaz - Mateo
    if(ui->pitch1->value() <= (LIMITE+5) && ui->pitch1->value() >= -(LIMITE+5))
    {
        setpointPitch = (char) ui->pitch1->value();
        QByteArray dato;
        dato.append(setpointPitch+128);
        GenerarTrama(&dato,0);
        EnviarDatos(dato);
    }else {
        ui->pitch1->setValue(setpointPitch);
    }
}

void Interfaz::on_roll2_editingFinished()
{
    //Cosas de la interfaz
    if(ui->roll2->value() <= (LIMITE+5) && ui->roll2->value() >= -(LIMITE+5))
    {
        setpointRoll = (char) ui->roll2->value();
        QByteArray dato;
        dato.append(setpointRoll+128);
        GenerarTrama(&dato,1);
        EnviarDatos(dato);
    }else {
        ui->roll2->setValue(setpointRoll);
    }
}

void Interfaz::on_yaw_valueChanged(const QString &arg1)
{
    if(ui->yaw->value() <= (LIMITE+5) && ui->yaw->value() >= -(LIMITE+5))
    {
        setpointYaw = (char) ui->yaw->value();
        QByteArray dato;
        dato.append(setpointYaw+128);
        GenerarTrama(&dato,2);
        EnviarDatos(dato);

    }else {
        ui->yaw->setValue(setpointYaw);
    }

}

void Interfaz::on_comboBoxPort_currentIndexChanged(int index)
{
    Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
}

void Interfaz::on_btnUpdate_clicked()
{
    //Cosas de comunicacion
    Port = nullptr;    //indica que el objeto puerto no esta creado;
    Portname = "";
    EnumerarPuertos();
}

void Interfaz::EnviarDatos(QByteArray buff)
{

    if(Port)
    {
       qint64 i;
       i = Port->write(buff);
       buff.clear();

       }
    else
    {
        QMessageBox::critical(this,"Error", QString::fromLatin1("Hay problemas con el envio de datos"));
        setpointPitch = 0;
        setpointRoll = 0;
        setpointYaw = 0;
        ui->yaw->setValue(0);
        ui->roll2->setValue(0);//reseteo los valores a 0 cuando se aprieta calibrar
        ui->pitch1->setValue(0);
    }
}

void Interfaz::GenerarTrama(QByteArray* buff, const int tipo)
{
    switch (tipo)
    {
        case 0:
            buff->prepend("PIT");
            break;
        case 1:
            buff->prepend("RLL");
            break;
        case 2:
            buff->prepend("YAW");
            break;
        case 3:
            buff->prepend("REC");
            break;
        default:
            buff->prepend("@");
            break;
    }

    buff->prepend('#');
    buff->append("@");
}

void Interfaz::AnalizarTrama(QByteArray buff)
{
    QByteArray aux;
    if(buff.size() > 3) aux.append(buff.mid(1,3));
    if(aux == "PIT")
    {
        unsigned char aux2;
        if( buff.size() > 4)
        {
            aux2 = (unsigned char) buff.at(4);
            pitch = (aux2 - 128);
//            if(pitch > 50)
//            {
//                qDebug() << "CACA";
//            }
//            qDebug() << "POS: " << buff;
        }

    }
    else if (aux == "RLL")
    {
        unsigned char aux2;
        if( buff.size() > 4)
        {
            aux2 = (unsigned char) buff.at(4);
            roll = (aux2 - 128);
        }
    }
    else if (aux == "YAW")
    {
        unsigned char aux2;
        if( buff.size() > 4)
        {
            aux2 = (unsigned char) buff.at(4);
            yaw = (aux2 - 128);
        }
    }
    else if (aux == "OUT")
    {
        unsigned char aux2;
        if( buff.size() > 4)
        {
            aux2 = (unsigned char) buff.at(4);
            out = (aux2 - 128);
        }
    }else if (aux == "DEB")
    {
        qDebug() << "Mensaje Analizado" << buff.mid(4, buff.size());
    }


}

void Interfaz::Recibiendo()
{
    QByteArray aux;
    aux.resize(int(Port->bytesAvailable()));
    aux = Port->readAll();

    if((index + aux.size()) >= 100)
    {
        /**Si me paso del tamaño que yo sete*/
        index=0;
        bufferCircular.clear();
    }else {
        //No sobreescribo ahi?
        bufferCircular.append(aux);
        index+=aux.size();
    }
}

void Interfaz::verificarTrama()
{
   static int auxIndex = 0;
   static int estado = 0;
   QByteArray buffRecTrama;

   buffRecTrama.resize(index - auxIndex);
   buffRecTrama.clear();

   for(int j = auxIndex; j < index; j++)
   {
       char dato = bufferCircular.at(j);
       static int i = 0;

       switch(estado)
       {
           case 0:
               if(dato == '#')
               {
                   buffRecTrama.append(dato);
                   i++;
                   estado = 1;
               }
               break;
           case 1:
               if(i < 4 && dato != '@' && dato != '#')
               {
                   buffRecTrama.append(dato);
                   i++;
               }
               else
               {
                   if(i == 4 && dato != '@' && dato != '#')
                   {
                       buffRecTrama.append(dato);
                       i++;
                       estado = 2;
                       //return;
                   }
                   else
                   {
                       buffRecTrama.clear();
                       i = 0;
                       estado = 0;
                   }
               }
               break;
           case 2:
               if(dato == '@')
               {
                   buffRecTrama.append(dato);
                   i++;
//                   qDebug() << buffRecTrama;
                   AnalizarTrama(buffRecTrama);
                   i = 0;
                   estado = 0;
               }else{
                   if(i < 4 - 1)	//Llenar hasta que te pases
                   {
                       i++;
                   }else{
                       buffRecTrama.clear();
                       i = 0;
                       estado = 0;
                   }
               }
               break;
           default:
               buffRecTrama.clear();
               i = 0;
               estado = 0;
               return;
       }

   }
   auxIndex = index;

}

void Interfaz::on_pushButtonConectar_clicked()
{
    if (!Port) //distinto de nulo
    {
        Port = new QSerialPort(Portname);
        Port->setBaudRate(QSerialPort::Baud9600); //velocidad
        Port->setFlowControl(QSerialPort::NoFlowControl);
        Port->setParity(QSerialPort::NoParity);
        Port->setDataBits(QSerialPort::Data8);
        Port->setStopBits(QSerialPort::OneStop);
        if(!Port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto " + Port->portName());
            delete Port;
            Port = nullptr;
        }
        else
        {
            ui->statusBar->showMessage("Conectado", 1000);
            HabilitarBotones(true);
            ui->pushButtonConectar->setText("Desconectar");
            connect(Port,SIGNAL(readyRead()),this,SLOT(Recibiendo())); //quien y que manda,receptor y slot(una funcion)
        }
    }
    else
    {
        HabilitarBotones(false);
        delete Port;
        Port = nullptr;
        ui->pushButtonConectar->setText("Conectar");
    }
}

void Interfaz::on_btnEnviar_clicked()
{
    //Cosas de la comunicacion
    QByteArray dato;
    QByteArray dato1;
    QByteArray dato2;

    dato.clear();
    dato1.clear();
    dato2.clear();


    dato.append(setpointPitch+128);
    dato1.append(setpointRoll+128);
    dato2.append(setpointYaw+128);

    GenerarTrama(&dato,PITCH);
    GenerarTrama(&dato1,ROLL);
    GenerarTrama(&dato2,YAW);

    EnviarDatos(dato);
    EnviarDatos(dato1);
    EnviarDatos(dato2);
}



void Interfaz::on_btnPlot_clicked()
{
//    //----------Para probar------------
//    QByteArray aux = "@PITA#";
//    AnalizarTrama(aux);
//    aux.clear();
//    aux.append("@ROLG#");
//    AnalizarTrama(aux);
//    aux.clear();
//    aux.append("@YAWP#");
//    AnalizarTrama(aux);
//    aux.clear();
//    aux.append("@DEBdaleBOCA#");
//    AnalizarTrama(aux);
//    //---------------------------------
    frmGrafico = new Plotting(nullptr, pitch, roll, yaw);
    frmGrafico->show();
}
