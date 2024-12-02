#include "professordashboard.h"
#include "ui_professordashboard.h"
#include <QFile>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QPixmap>


ProfessorDashboard::ProfessorDashboard(QSqlDatabase &db, const QString &userType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfessorDashboard),
    database(db)  // Initialize the database reference
{
    ui->setupUi(this);

    // Set the window title based on the user type
    setWindowTitle(userType + " Dashboard");

    // Nintendo
    QPixmap pix5("../../images/(38)professor.jpg");
    int w5 = ui ->professor->width();
    int h5 = ui ->professor->height();
    ui->professor->setPixmap(pix5.scaled(w5,h5,Qt::KeepAspectRatio));

}

ProfessorDashboard::~ProfessorDashboard()
{
    delete ui;
}

void ProfessorDashboard::on_selectImageButton_clicked()
{
    // Open a file dialog to select an image
    selectedImagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!selectedImagePath.isEmpty()) {
        // Display the selected image in the label
        QPixmap pixmap(selectedImagePath);
        ui->imagePreviewLabel->setPixmap(pixmap.scaled(ui->imagePreviewLabel->size(), Qt::KeepAspectRatio));
    }
}

void ProfessorDashboard::on_addCardButton_clicked()
{
    QString concept = ui->conceptLineEdit->text();

    if (concept.isEmpty() || selectedImagePath.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a concept and select an image.");
        return;
    }

    QFile file(selectedImagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "File Error", "Failed to open the image file.");
        return;
    }

    QByteArray imageData = file.readAll();
    file.close();

    // Compute image hash
    QByteArray imageHash = QCryptographicHash::hash(imageData, QCryptographicHash::Sha256);

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM cards WHERE image_hash = :image_hash");
    checkQuery.bindValue(":image_hash", imageHash);

    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "Duplicate Image", "This image already exists in the database.");
            return;
        }
    } else {
        qDebug() << "Database Error: " << checkQuery.lastError().text();
        QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO cards (concept, image, image_hash) VALUES (:concept, :image, :image_hash)");
    query.bindValue(":concept", concept);
    query.bindValue(":image", imageData);
    query.bindValue(":image_hash", imageHash);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Card added successfully!");
        ui->conceptLineEdit->clear();
        ui->imagePreviewLabel->clear();
        selectedImagePath.clear();
    } else {
        if (query.lastError().nativeErrorCode() == "2067" || query.lastError().text().contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "Duplicate Entry", "This concept or image already exists in the database.");
        } else {
            qDebug() << "Database Error: " << query.lastError().text();
            QMessageBox::critical(this, "Database Error", query.lastError().text());
        }
    }
}
