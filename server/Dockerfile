# Use a lightweight Python image
FROM python:3.9-slim

# Set the working directory inside the container
WORKDIR /app

# Copy the requirements file and install dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy the application code
COPY app.py .

# Expose the port the app will listen on (port 7000 as requested)
EXPOSE 7000

# Set environment variables for configuration (Optional but Recommended)
# You can also pass these during docker run or in docker-compose
ENV SERVER_CURRENT_VERSION="1.9"
ENV CSV_DOWNLOAD_URL="http://your_vps_ip_or_domain:your_csv_port/data/latest.csv" # !! Update this !!

# Command to run the application using Gunicorn
# -w: number of worker processes (adjust based on your VPS resources)
# -b: bind address and port
# app:app: points to the Flask application instance named 'app' inside the 'app.py' module
CMD ["gunicorn", "-w", "4", "-b", "0.0.0.0:7000", "app:app"]