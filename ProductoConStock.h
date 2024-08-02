#ifndef PRODUCTO_CON_STOCK_H
#define PRODUCTO_CON_STOCK_H

#include "Producto.h"
#include <QTextEdit>

class ProductoConStock : public Producto {
private:
    int cantidad;

public:
    ProductoConStock(const std::string& nombre, double precio, const std::string& descripcion, int cantidad)
        : Producto(nombre, precio, descripcion), cantidad(cantidad) {}

    double calcularValorTotal() const override {
        return precio * cantidad;
    }

    void mostrarInformacion(QTextEdit* textEdit) const override {
        textEdit->append(QString("Nombre: %1").arg(QString::fromStdString(nombre)));
        textEdit->append(QString("Precio: %1").arg(precio));
        textEdit->append(QString("Descripción: %1").arg(QString::fromStdString(descripcion)));
        textEdit->append(QString("Cantidad en Stock: %1").arg(cantidad));
        textEdit->append(QString("Valor Total: %1").arg(calcularValorTotal()));
        textEdit->append("");
    }

    ~ProductoConStock() override {}
};

#endif // PRODUCTO_CON_STOCK_H
