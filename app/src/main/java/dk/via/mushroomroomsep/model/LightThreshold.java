package dk.via.mushroomroomsep.model;

import java.time.LocalDateTime;

public class LightThreshold {

    private int id;
    private double lightLevel;
    private LocalDateTime timeStamp;
    private String musId;

    public LightThreshold(int id, double lightLevel, LocalDateTime timeStamp, String musId) {
        this.id = id;
        this.lightLevel = lightLevel;
        this.timeStamp = timeStamp;
        this.musId = musId;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getLightLevel() {
        return lightLevel;
    }

    public void setLightLevel(double lightLevel) {
        this.lightLevel = lightLevel;
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
