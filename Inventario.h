#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Producto.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <QString>
#include <QTextEdit>

class Inventario {
private:
    std::vector<std::unique_ptr<Producto>> productos;

public:
    void agregarProducto(std::unique_ptr<Producto> producto) {
        productos.push_back(std::move(producto));
    }

    bool eliminarProducto(const std::string& nombre) {
        auto it = std::remove_if(productos.begin(), productos.end(),
                                 [&nombre](const std::unique_ptr<Producto>& producto) {
                                     return producto->getNombre() == nombre;
                                 });

        bool eliminado = it != productos.end();
        productos.erase(it, productos.end());
        return eliminado;
    }

    size_t obtenerTamanioInventario() const {
        return productos.size();
    }

    void mostrarInventario(QTextEdit* textEdit) const {
        textEdit->clear();

        for (const auto& producto : productos) {
            producto->mostrarInformacion(textEdit);
        }
    }


    double calcularValorInventario() const {
        double valorTotal = 0.0;
        for (const auto& producto : productos) {
            valorTotal += producto->calcularValorTotal();
        }
        return valorTotal;
    }
};

#endif // INVENTARIO_H
