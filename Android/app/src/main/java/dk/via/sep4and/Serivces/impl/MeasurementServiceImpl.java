package dk.via.sep4and.Serivces.impl;

import androidx.lifecycle.MutableLiveData;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import dk.via.sep4and.Model.Measurement;
import dk.via.sep4and.Networking.MeasurementApi;
import dk.via.sep4and.Serivces.ApiGenerator;
import dk.via.sep4and.Serivces.MeasurmentService;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MeasurementServiceImpl implements MeasurmentService {


    private MutableLiveData<Measurement> measurement;
    private MutableLiveData<String> error;

    private static MeasurmentService instance;
    private static Lock lock = new ReentrantLock();

    private MeasurementApi measurementApi;

    public MeasurementServiceImpl() {
        measurement = new MutableLiveData<>();
        error = new MutableLiveData<>();
        measurementApi = ApiGenerator.getMeasurementApi();
    }

    public static MeasurmentService getInstance() {
        if (instance == null) {
            synchronized (lock) {
                if (instance == null) {
                    instance = new MeasurementServiceImpl();
                }
            }
        }
        return instance;
    }

    @Override
    public void getMeasurment(long id) {
        Call<Measurement> call = measurementApi.getMeasurment(id);

        call.enqueue(new Callback<Measurement>() {
            @Override
            public void onResponse(Call<Measurement> call, Response<Measurement> response) {
                if (response.isSuccessful()){
                    measurement.setValue(response.body());
                }
                else{
                    error.setValue("Request not successful for getMeasurment");
                }
            }

            @Override
            public void onFailure(Call<Measurement> call, Throwable t) {
                error.setValue(t.getMessage());
            }
        });
    }
}
