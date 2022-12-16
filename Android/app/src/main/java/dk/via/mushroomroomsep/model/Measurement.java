package dk.via.mushroomroomsep.model;

import java.time.LocalDateTime;

public class Measurement {

    private int measureId;

    private double co2;

    private double humidity;

    private double temperature;

    private double lightLevel;

    private LocalDateTime timestamp;

    public Measurement() {

    }

    public Measurement(int id, double co2, double humidity, double temperature, double lightLevel, LocalDateTime timeStamp) {
        this.measureId = id;
        this.co2 = co2;
        this.humidity = humidity;
        this.temperature = temperature;
        this.lightLevel = lightLevel;
        this.timestamp = timeStamp;
    }

    public int getId(){
        return measureId;
    }

    public double getCo2() {
        return co2;
    }

    public double getHumidity() {
        return humidity;
    }

    public double getTemperature() {
        return temperature;
    }

    public LocalDateTime getTimeStamp() {
        return timestamp;
    }

    public double getLightLevel() {
        return lightLevel;
    }
}


