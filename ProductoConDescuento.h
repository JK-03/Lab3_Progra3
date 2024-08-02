#ifndef PRODUCTO_CON_DESCUENTO_H
#define PRODUCTO_CON_DESCUENTO_H

#include "Producto.h"
#include <QTextEdit>

class ProductoConDescuento : public Producto {
private:
    double descuento;

public:
    ProductoConDescuento(const std::string& nombre, double precio, const std::string& descripcion, double descuento)
        : Producto(nombre, precio, descripcion), descuento(descuento) {}

    double calcularValorTotal() const override {
        double precioConDescuento = precio - (precio * (descuento / 100.0));
        return precioConDescuento;
    }

    void mostrarInformacion(QTextEdit* textEdit) const override {
        textEdit->append(QString("Nombre: %1").arg(QString::fromStdString(nombre)));
        textEdit->append(QString("Precio Original: %1").arg(precio));
        textEdit->append(QString("Descripción: %1").arg(QString::fromStdString(descripcion)));
        textEdit->append(QString("Descuento: %1%").arg(descuento));
        textEdit->append(QString("Valor Total: %1").arg(calcularValorTotal()));
        textEdit->append("");
    }

    ~ProductoConDescuento() override {}
};

#endif // PRODUCTO_CON_DESCUENTO_H
