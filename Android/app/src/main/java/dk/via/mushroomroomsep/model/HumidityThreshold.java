package dk.via.mushroomroomsep.model;

import java.time.LocalDateTime;

public class HumidityThreshold {


    private int id;
    private double humidityLevel;
    private LocalDateTime timeStamp;
    private String musId;

    public HumidityThreshold(int id, double humidityLevel, LocalDateTime timeStamp, String musId) {
        this.id = id;
        this.humidityLevel = humidityLevel;
        this.timeStamp = timeStamp;
        this.musId = musId;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getHumidityLevel() {
        return humidityLevel;
    }

    public void setHumidityLevel(double humidityLevel) {
        this.humidityLevel = humidityLevel;
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
