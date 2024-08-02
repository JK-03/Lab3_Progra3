#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <QTextEdit>

class Producto {
protected:
    std::string nombre;
    double precio;
    std::string descripcion;

public:
    Producto(const std::string& nombre, double precio, const std::string& descripcion)
        : nombre(nombre), precio(precio), descripcion(descripcion) {}

    std::string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    std::string getDescripcion() const { return descripcion; }

    virtual double calcularValorTotal() const = 0;
    virtual void mostrarInformacion(QTextEdit* textEdit) const = 0;
    virtual ~Producto() {}
};

#endif // PRODUCTO_H
