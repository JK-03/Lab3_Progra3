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

//MENÚ
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

//FUNCIONES
void cframe::agregarProducto() {
    QString nombreProducto = ui->LE_Nombre->text();
    double precio = ui->spb_Precio->value();
    QString descripcion = ui->TE_Descripcion->toPlainText();
    int adicional = ui->spb_Adicional->value();

    int tipoProducto = ui->comboBox_Tipo->currentIndex();
    std::unique_ptr<Producto> producto;

    if (tipoProducto == 0) {
        if (adicional > 100) {
            QMessageBox::warning(this, "Advertencia", "El descuento no puede ser mayor al 100%");
            return;
        }
        if (adicional > 0) {
            producto = std::make_unique<ProductoConDescuento>(nombreProducto.toStdString(), precio, descripcion.toStdString(), adicional);
        } else {
            QMessageBox::warning(this, "Advertencia", "Para ProductoConDescuento el descuento debe ser mayor a 0.");
            return;
        }
    } else if (tipoProducto == 1) {
        producto = std::make_unique<ProductoConStock>(nombreProducto.toStdString(), precio, descripcion.toStdString(), adicional);
    } else {
        QMessageBox::warning(this, "Advertencia", "Tipo de producto no válido.");
        return;
    }

    if (producto) {
        inventario.agregarProducto(std::move(producto));
        QMessageBox::information(this, "Éxito", "El producto se ha agregado exitosamente al inventario.");
        size_t tamano = inventario.obtenerTamanioInventario();
        qDebug() << "El tamaño del inventario es:" << tamano;
    }
}
void cframe::eliminarProducto() {
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

void cframe::mostrarProducto()
{
    inventario.mostrarInventario(ui->TE_ProductosLista);
}

void cframe::mostrarValorTotalInventario()
{
    double valorTotal = inventario.calcularValorInventario();

    QMessageBox::information(this, "Valor Total del Inventario", "Valor Total del Inventario: " + QString::number(valorTotal));
}


//IMPLEMENTACIÓN FUNCIONES A BOTONES
void cframe::on_pushButton_2_clicked()
{
    agregarProducto();
}

void cframe::on_pushButton_3_clicked()
{
    eliminarProducto();
}


