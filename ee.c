#include <msgpack.hpp>
// ... conexión al socket /var/run/arduino-router.sock, registro con $/register("get_mensaje") ...

// Cuando llega la petición get_mensaje(id):
std::string obtenerMensaje(int id) {
    switch (id) {
        case 1: return "Boton presionado!";
        case 2: return "Temperatura OK";
        default: return "Mensaje desconocido";
    }
}
// Empaquetar el std::string como respuesta MessagePack y devolverlo por el socket