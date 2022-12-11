package dk.via.sep4and.Model;

import com.google.gson.annotations.SerializedName;

import java.time.LocalDateTime;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;


public class Measurement {

    private int id;

    private double co2;

    private double humidity;

    private double temperature;

    private LocalDateTime timeStamp;

    public Measurement() {

    }

    public Measurement(int id, double co2, double humidity, double temperature, LocalDateTime timeStamp) {
        this.id = id;
        this.co2 = co2;
        this.humidity = humidity;
        this.temperature = temperature;
        this.timeStamp = timeStamp;
    }

    public int getId(){
        return id;
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
        return timeStamp;
    }
}

