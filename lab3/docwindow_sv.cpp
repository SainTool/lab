#include "docwindow_sv.h"
#include "QFileDialog"
#include "QTextStream"
DocWindow_SV::DocWindow_SV(QWidget* pwgt): QTextEdit(pwgt)
{

}
void DocWindow_SV::slotLoad(){
    QString str = QFileDialog::getOpenFileName();
    if(str.isEmpty()){
        return;
    }
    QFile file(str);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
    }
    m_strFileName = str;
    emit changeWindowTitle(m_strFileName);

}
void DocWindow_SV::slotSaveAs(){
    QString str = QFileDialog::getSaveFileName(0, m_strFileName);
    if(!str.isEmpty()){
        m_strFileName = str;
        slotSave();
    }
    QFile file(m_strFileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream(&file)<<toPlainText();
    }
    file.close();
    emit changeWindowTitle(m_strFileName);
}
void DocWindow_SV::slotSave(){
    if(m_strFileName.isEmpty()){
        slotSaveAs();
        return;
    }
}
