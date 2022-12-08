package dk.via.sep4and.Model;

import java.time.LocalDateTime;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@AllArgsConstructor
@ToString
public class Measurement {
    private int id;
    private double Co2;
    private double Humidity;
    private double Temperature;
    private LocalDateTime TimeStamp;

}

