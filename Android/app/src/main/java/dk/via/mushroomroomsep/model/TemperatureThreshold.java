package dk.via.mushroomroomsep.model;

import java.time.LocalDateTime;

public class TemperatureThreshold {

    private int id;
    private double temperatureLevel;
    private LocalDateTime timeStamp;
    private String musId;

    public TemperatureThreshold(int id, double temperatureLevel, LocalDateTime timeStamp, String musId) {
        this.id = id;
        this.temperatureLevel = temperatureLevel;
        this.timeStamp = timeStamp;
        this.musId = musId;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getTemperatureLevel() {
        return temperatureLevel;
    }

    public void setTemperatureLevel(double temperatureLevel) {
        this.temperatureLevel = temperatureLevel;
    }

    public LocalDateTime getTimeStamp() {
        return timeStamp;
    }

    public void setTimeStamp(LocalDateTime timeStamp) {
        this.timeStamp = timeStamp;
    }

    public String getMusId() {
        return musId;
    }

    public void setMusId(String musId) {
        this.musId = musId;
    }
}
