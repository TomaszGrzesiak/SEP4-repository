package dk.via.mushroomroomsep.network;

import dk.via.mushroomroomsep.model.Co2Threshold;
import dk.via.mushroomroomsep.model.HumidityThreshold;
import dk.via.mushroomroomsep.model.LightThreshold;
import dk.via.mushroomroomsep.model.Measurement;
import dk.via.mushroomroomsep.model.TemperatureThreshold;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.GET;

public interface MeasurementAPI {

    @GET("Measurement")
    Call<Measurement> getMeasurements();

    @GET("Co2ThreshhoId")
    Call<Co2Threshold> getCo2ThresholdId();

    @GET("HumidityThreshold")
    Call<HumidityThreshold> getHumidityThreshold();

    @GET("LightThreshold")
    Call<LightThreshold> getLightThreshold();

    @GET("TemperatureThreshold")
    Call<TemperatureThreshold> getTemperatureThreshold();

    @GET("measurement/Measurement/history")
    Call<List<Measurement>> getMeasurementHistory();



}
