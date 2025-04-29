from flask import Flask, request, send_file, jsonify

app = Flask(__name__)

# Endpoint para recibir la versión del cliente
@app.route("/get-version", methods=["POST"])
def get_version():
    client_version = request.json.get('version')
    print(f"Received version from client: {client_version}")

    server_version = "1.9"  # Versión interna del servidor
    print(f"Server current version: {server_version}")

    if not client_version:
        return jsonify({"error": "Missing 'version' parameter."}), 400

    if client_version != server_version:
        # Si la versión no coincide, devolver el archivo CSV
        return send_file("/data/latest.csv", as_attachment=True)

    # Si la versión es igual, devolver "ok"
    return jsonify({"status": "ok"})

if __name__ == "__main__":
    # Ejecuta la app Flask en el puerto 7001
    app.run(host="0.0.0.0", port=7001, debug=True)
