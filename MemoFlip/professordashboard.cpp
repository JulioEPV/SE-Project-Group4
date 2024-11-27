#include "professordashboard.h"
#include "ui_professordashboard.h"
#include <QFile>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QMessageBox>

ProfessorDashboard::ProfessorDashboard(QSqlDatabase &db, const QString &userType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfessorDashboard),
    database(db)  // Initialize the database reference
{
    ui->setupUi(this);

    // Set the window title based on the user type
    setWindowTitle(userType + " Dashboard");

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

    QByteArray imageData = file.readAll();  // Read image as bytes
    file.close();

    qDebug() << "Concept: " << concept;  // Debug: Print concept
    qDebug() << "Image data size: " << imageData.size();  // Debug: Print size of image data

    QSqlQuery query;
    query.prepare("INSERT INTO cards (concept, image) VALUES (:concept, :image)");
    query.bindValue(":concept", concept);
    query.bindValue(":image", imageData);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Card added successfully!");
        ui->conceptLineEdit->clear();
        ui->imagePreviewLabel->clear();
        selectedImagePath.clear();
    } else {
        qDebug() << "Database Error: " << query.lastError().text();  // Debug: Print database error
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}
