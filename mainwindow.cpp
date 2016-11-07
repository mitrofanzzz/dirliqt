#include "mainwindow.h"
#include "ui_mainwindow.h"

QDir dir_path;
// QDir t_dir_path;
QFileInfoList result_FileList;

QFileInfoList GetListFromDir(QDir t_d_path);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog *setdir = new QFileDialog;
    setdir->setFileMode(QFileDialog::DirectoryOnly);
    QString path = setdir->getExistingDirectory(this, tr("Open Directory"), "c:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->label->setText(path);
}

void MainWindow::on_pushButton_3_clicked()
{
    QFileInfoList Filelist;
    QDir t_dir_path;
    QFileInfoList t_Filelist;
    int nrow, crow;
    int ncolumn;
    QStringList list;

    ncolumn = 2;
    crow = 0;

    //ui->listWidget->clear();
    ui->tableWidget->clear();

    dir_path.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    dir_path.setSorting(QDir::DirsFirst | QDir::Name);
    dir_path = ui->label->text();
//    Filelist = dir_path.entryInfoList();
    //ui->listWidget->addItem(dir_path.path());
    GetListFromDir(dir_path);
    ui->tableWidget->setColumnCount( ncolumn );
    nrow = result_FileList.count();
    ui->tableWidget->setRowCount( nrow );
    ui->tableWidget->insertRow(nrow+1);

    list << "Path" << "Size (KB)";
    ui->tableWidget->setHorizontalHeaderLabels(list);

    QTableWidgetItem Paths[nrow+1];
    QTableWidgetItem Sizes[nrow+1];
    QTableWidgetItem Item;

    foreach (QFileInfo txt, result_FileList) {
        if (txt.isDir()){
            Paths[crow] = QTableWidgetItem(txt.absoluteFilePath());
            Sizes[crow] = QTableWidgetItem("DIR");
        } else if (txt.isFile()){
            Paths[crow] = QTableWidgetItem(txt.absoluteFilePath());
            Sizes[crow] = QTableWidgetItem( QString::number ( txt.size()/(1024) ) );
        }
        crow++;
    }

    crow = 0;
    foreach (QFileInfo txt, result_FileList) {
        if (txt.isDir()){
            Item = Paths[crow];
            ui->tableWidget->setItem(crow , 0, new QTableWidgetItem(Item));
            Item = Sizes[crow];
            ui->tableWidget->setItem(crow, 1, new QTableWidgetItem(Item));
        } else if (txt.isFile()){
            Item = Paths[crow];
            ui->tableWidget->setItem(crow, 0, new QTableWidgetItem(Item));
            Item = Sizes[crow];
            ui->tableWidget->setItem(crow, 1, new QTableWidgetItem(Item));
        }
        crow++;
    }
}

QFileInfoList GetListFromDir(QDir t_d_path) {

    QFileInfoList locFilelist;
    QDir loc_t_dir_path;
    QFileInfoList loc_t_Filelist;


    loc_t_dir_path = t_d_path;
    loc_t_dir_path.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    loc_t_dir_path.setSorting(QDir::DirsFirst | QDir::Name);
    loc_t_Filelist = loc_t_dir_path.entryInfoList();

    foreach (QFileInfo tItm, loc_t_Filelist) {
        if (tItm.isDir()){
            result_FileList += tItm.absoluteFilePath();
            GetListFromDir(tItm.absoluteFilePath());
        } else if (tItm.isFile()){
           result_FileList += tItm.absoluteFilePath();
        }
    }
    return result_FileList;
}
