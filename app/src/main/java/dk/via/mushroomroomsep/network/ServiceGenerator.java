package dk.via.mushroomroomsep.network;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class ServiceGenerator {
    private static MeasurementAPI measurementAPI;

  private static String BASE_URL = "https://localhost:7007/Measurement/";


    public static MeasurementAPI getMeasurementAPI(){
        if(measurementAPI == null) {
            measurementAPI = new Retrofit.Builder()
                    .baseUrl(BASE_URL)
                    .addConverterFactory(GsonConverterFactory.create())
                    .build()
                    .create(MeasurementAPI.class);
            System.out.println("Api instance lazy iniciated");
        }
        return measurementAPI;
    }
}
