#include "cframe.h"
#include "ui_cframe.h"
#include "ProductoConStock.h"
#include "ProductoConDescuento.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QDebug>

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);

    this->setWindowTitle("Laboratorio #3");

    ui->tabWidget->setCurrentIndex(0);
}

cframe::~cframe()
{
    delete ui;
}

void cframe::on_pushButton_clicked()
{
    std::string opcion = "";

    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcion6 = msgBox.addButton("Salir", QMessageBox::ActionRole);
    QPushButton *opcion5 = msgBox.addButton("Valor Total del Inventario", QMessageBox::ActionRole);
    QPushButton *opcion4 = msgBox.addButton("Mostrar Producto", QMessageBox::ActionRole);
    QPushButton *opcion3 = msgBox.addButton("Eliminar Producto", QMessageBox::ActionRole);
    QPushButton *opcion2 = msgBox.addButton("Agregar Producto", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcion2) {
        ui->tabWidget->setCurrentIndex(1);
    } else if (msgBox.clickedButton() == opcion3) {
        ui->tabWidget->setCurrentIndex(2);
    } else if (msgBox.clickedButton() == opcion4) {
        ui->tabWidget->setCurrentIndex(3);
        mostrarProducto();
    } else if (msgBox.clickedButton() == opcion5) {
        mostrarValorTotalInventario();
    } else if (msgBox.clickedButton() == opcion6) {
        this->close();
    }
}

//Funciones
void cframe::mostrarProducto()
{
    inventario.mostrarInventario(ui->TE_ProductosLista);
}

void cframe::mostrarValorTotalInventario()
{
    double valorTotal = inventario.calcularValorInventario();
    ui->TE_ProductosLista->clear();
    ui->TE_ProductosLista->append("Valor Total del Inventario:");
    ui->TE_ProductosLista->append(QString::number(valorTotal));
}





void cframe::on_pushButton_2_clicked()
{
    QString nombreProducto = ui->LE_Nombre->text();
    double precio = ui->spb_Precio->value();
    QString descripcion = ui->TE_Descripcion->toPlainText();
    double descuento = ui->spb_Descuento->value();
    int cantidad = ui->spb_Cantidad->value();

    std::unique_ptr<Producto> producto;

    if (descuento > 100) {
        QMessageBox::warning(this, "Advertencia", "El descuento no puede ser mayor al 100%");
        return;
    }

    if (descuento > 0) {
        producto = std::make_unique<ProductoConDescuento>(nombreProducto.toStdString(), precio, descripcion.toStdString(), descuento);
    } else {
        bool ok;
        if (descuento == 0) {
            cantidad = QInputDialog::getInt(this, "Cantidad", "Ingrese la cantidad:", cantidad, 0, 10000, 1, &ok);
            if (!ok) {
                return;
            }
        }

        producto = std::make_unique<ProductoConStock>(nombreProducto.toStdString(), precio, descripcion.toStdString(), cantidad);
    }

    if (producto) {
        inventario.agregarProducto(std::move(producto));

        QMessageBox::information(this, "Éxito", "El producto se ha agregado exitosamente al inventario.");

        size_t tamano = inventario.obtenerTamanioInventario();
        qDebug() << "El tamaño del inventario es:" << tamano;
    }
}

void cframe::on_pushButton_3_clicked()
{
    QString nombreProducto = ui->LE_NombreEliminar->text();

    if (!nombreProducto.isEmpty()) {
        bool eliminado = inventario.eliminarProducto(nombreProducto.toStdString());

        if (eliminado) {
            QMessageBox::information(this, "Producto Eliminado", "El producto ha sido eliminado exitosamente.");
        } else {
            QMessageBox::warning(this, "Error", "No se encontró el producto para eliminar.");
        }
    } else {
        QMessageBox::warning(this, "Advertencia", "Por favor, ingrese el nombre del producto a eliminar.");
    }
}


