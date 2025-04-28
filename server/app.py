from flask import Flask, request, jsonify
import os

app = Flask(__name__)

# --- Configuration ---
# This is the version that the server considers current
SERVER_CURRENT_VERSION = os.environ.get('SERVER_CURRENT_VERSION', '1.9') # Default to 1.9

# This is the URL where the ESP32 should download the latest CSV file if needed
# !! IMPORTANT: Replace this with the actual public URL where your CSV file is hosted !!
# This could be served by Nginx, Apache, or even a separate Flask endpoint
CSV_DOWNLOAD_URL = os.environ.get('CSV_DOWNLOAD_URL', 'http://http://168.231.68.187:7000/data/latest.csv')

# --- Endpoint for Version Check ---
@app.route('/get-version', methods=['GET'])
def get_version():
    """
    Handles GET requests to check the ESP32 version against the server version.
    Expects a query parameter 'version'.
    """
    esp32_version = request.args.get('version')

    print(f"Received version from ESP32: {esp32_version}")
    print(f"Server current version: {SERVER_CURRENT_VERSION}")

    # Check if the version parameter was provided
    if esp32_version is None:
        print("Error: 'version' parameter is missing.")
        return jsonify({
            "status": "error",
            "message": "'version' query parameter is required."
        }), 400 # Bad Request

    # Compare versions
    if esp32_version == SERVER_CURRENT_VERSION:
        response = {
            "status": "ok",
            "message": "Versions match. No update needed."
        }
        print("Versions match.")
    else:
        response = {
            "status": "update_required",
            "message": "Version mismatch. Update required.",
            "server_version": SERVER_CURRENT_VERSION, # Optionally send server version
            "csv_url": CSV_DOWNLOAD_URL
        }
        print("Version mismatch. Sending CSV download URL.")

    # Return the JSON response
    return jsonify(response), 200 # OK

# --- Health Check (Optional but Recommended) ---
@app.route('/health', methods=['GET'])
def health_check():
    """Simple health check endpoint."""
    return jsonify({"status": "healthy"}), 200

# --- Run the application ---
if __name__ == '__main__':
    # Use a production-ready WSGI server like Gunicorn in Docker
    # The command to run with gunicorn will be in the Dockerfile/docker-compose
    # This block is mainly for local testing outside of Docker
    print("Running Flask development server (use Gunicorn/Waitress in production)")
    app.run(host='0.0.0.0', port=7000, debug=True) # debug=True is useful for testing