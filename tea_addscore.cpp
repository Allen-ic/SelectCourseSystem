#include "mainwindow.h"
#include "tea_addscore.h"
#include "ui_tea_addscore.h"
#include "QString"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include<QPushButton>
#include<QLineEdit>
tea_addscore::tea_addscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tea_addscore)
{
    ui->setupUi(this);

}


tea_addscore::~tea_addscore()
{
    delete ui;
}
void tea_addscore::on_btn_addscore_add_clicked()
{

    QString name=this->ui->le_addscore_name->text();
    QString id=this->ui->le_addscore_id->text();
    QString classnum=this->ui->le_addscore_class->text();
    QString cpp=this->ui->le_addscore_math->text();
    QString jav=this->ui->le_addscore_eng->text();
    QString pyt=this->ui->le_addscore_phy->text();
    int temp=cpp.toInt()+jav.toInt()+pyt.toInt();
    QString sum=QString::number(temp);
    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"班级："+classnum+"\n"+
            "C++："+cpp+"\n"+"Java："+jav+"\n"+"Python："+pyt+"\n"+"总分："+sum+"\n";
    QString information=name+" "+id+" "+classnum+" "+cpp+" "+jav+" "+pyt+" "+sum;

    bool charge=name.length()<1||id.length()<9||classnum.length()<6||
                cpp.length()<1||jav.length()<1||pyt.length()<1;
    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }
    else
    {
       int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
       if(ret==0)
          {  writeIn(information);

             QSqlDatabase database;
             if (QSqlDatabase::contains("qt_sql_default_connection"))
             {
                 database = QSqlDatabase::database("qt_sql_default_connection");
             }
             else
             {
                 database = QSqlDatabase::addDatabase("QSQLITE");
                 database.setDatabaseName("MyDataBase.db");
                 database.setUserName("XingYeZhiXia");
                 database.setPassword("123456");
             }

             if (!database.open())
             {
                 qDebug() << "Error: Failed to connect database." << database.lastError();
             }
             else
             {
                 // do something
                 //操控数据库
                 //创建表
                 QSqlQuery sql_query;
                 QString insert_sql = "insert into Score values (?, ?, ?, ?, ?, ?, ?)";
                 sql_query.prepare(insert_sql);
                 QString name=this->ui->le_addscore_name->text();
                 QString id=this->ui->le_addscore_id->text();
                 QString classnum=this->ui->le_addscore_class->text();
                 QString cpp=this->ui->le_addscore_math->text();
                 QString jav=this->ui->le_addscore_eng->text();
                 QString pyt=this->ui->le_addscore_phy->text();
                 int total=cpp.toInt()+jav.toInt()+pyt.toInt();
                 qDebug()<<name<<id<<classnum<<cpp<<jav<<pyt;
                 sql_query.addBindValue(id);
                 sql_query.addBindValue(name);
                 sql_query.addBindValue(classnum);
                 sql_query.addBindValue(cpp);
                 sql_query.addBindValue(jav);
                 sql_query.addBindValue(pyt);
                 sql_query.addBindValue(total);

                 if(!sql_query.exec())
                 {
                     qDebug() << sql_query.lastError();
                 }
                 else
                 {
                     qDebug() << "inserted successfully!";
                 }
              }

             database.close();
            }
      }
  }

void tea_addscore::writeIn(QString information)
{
    this->ui->le_addscore_name->clear();
    this->ui->le_addscore_id->clear();
    this->ui->le_addscore_class->clear();
    this->ui->le_addscore_math->clear();
    this->ui->le_addscore_eng->clear();
    this->ui->le_addscore_phy->clear();
    this->ui->le_addscore_name->setFocus();
    QFile mFile("score.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<information<<"\n";
    mFile.flush();
    mFile.close();
}

void tea_addscore::on_btn_addscore_cancel_clicked()
{
    this->close();
}

/*tea_addscore::tea_addscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tea_addscore)
{
    ui->setupUi(this);

}


tea_addscore::~tea_addscore()
{
    delete ui;
}


void tea_addscore::on_btn_addscore_add_clicked()
{

    QString name=this->ui->le_addscore_name->text();
    QString id=this->ui->le_addscore_id->text();
    QString classnum=this->ui->le_addscore_class->text();
    QString cpp=this->ui->le_addscore_math->text();
    QString jav=this->ui->le_addscore_eng->text();
    QString pyt=this->ui->le_addscore_phy->text();
    int temp=cpp.toInt()+jav.toInt()+pyt.toInt();
    QString sum=QString::number(temp);
    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"班级："+classnum+"\n"+
            "C++："+cpp+"\n"+"Java："+jav+"\n"+"Python："+pyt+"\n"+"总分："+sum+"\n";
    QString information=name+" "+id+" "+classnum+" "+cpp+" "+jav+" "+pyt+" "+sum;

    bool charge=name.length()<1||id.length()<9||classnum.length()<6||
                cpp.length()<1||jav.length()<1||pyt.length()<1;
    if(charge==1)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }
    else
    {
       int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
       if(ret==0)
          {
             writeIn(information);
          }
    }
}

void tea_addscore::writeIn(QString information)
{
    this->ui->le_addscore_name->clear();
    this->ui->le_addscore_id->clear();
    this->ui->le_addscore_class->clear();
    this->ui->le_addscore_math->clear();
    this->ui->le_addscore_eng->clear();
    this->ui->le_addscore_phy->clear();
    this->ui->le_addscore_name->setFocus();
    QFile mFile("score.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<information<<"\n";
    mFile.flush();
    mFile.close();
}

void tea_addscore::on_btn_addscore_cancel_clicked()
{
    this->close();
}
*/
