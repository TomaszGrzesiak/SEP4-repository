package dk.via.sep4and.Serivces;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import dk.via.sep4and.Networking.MeasurementApi;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class ApiGenerator {

    private static MeasurementApi measurementApi;
    private static Lock lock = new ReentrantLock();


    private static String BASE_URL = "https://localhost:5001/swagger/";


    public static MeasurementApi getMeasurementApi() {
        if(measurementApi == null) {
            synchronized (lock) {
                if(measurementApi == null) {
                    measurementApi = new Retrofit.Builder().baseUrl(BASE_URL)
                            .addConverterFactory(GsonConverterFactory.create()).build().create(MeasurementApi.class);
                }
            }
        }
        return measurementApi;
    }
}
