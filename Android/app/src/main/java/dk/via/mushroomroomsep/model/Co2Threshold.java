package dk.via.mushroomroomsep.model;

import java.time.LocalDateTime;

public class Co2Threshold {

    private int id;
    private double co2Level;
    private LocalDateTime timeStamp;
    private String musid;

    public Co2Threshold(int id, double co2Level, LocalDateTime timeStamp, String musid) {
        this.id = id;
        this.co2Level = co2Level;
        this.timeStamp = timeStamp;
        this.musid = musid;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getCo2Level() {
        return co2Level;
    }

    public void setCo2Level(double co2Level) {
        this.co2Level = co2Level;
    }

    public LocalDateTime getTimeStamp() {
        return timeStamp;
    }

    public void setTimeStamp(LocalDateTime timeStamp) {
        this.timeStamp = timeStamp;
    }

    public String getMusid() {
        return musid;
    }

    public void setMusid(String musid) {
        this.musid = musid;
    }
}
