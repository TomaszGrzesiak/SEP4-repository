package dk.via.mushroomroomsep.view;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;

import dk.via.mushroomroomsep.model.Measurement;
import dk.via.mushroomroomsep.repository.MeasurementRepository;

import java.util.List;

public class MeasurementFragmentViewModel extends ViewModel {

    private static final String TAG = "MeasurementFragmentViewModel";

    private final MeasurementRepository measurementRepository = MeasurementRepository.getInstance();

    private final LiveData<List<Measurement>> measurementHistoryListLiveData;

    public MeasurementFragmentViewModel(){

        measurementHistoryListLiveData = getMeasurementHistoryListLiveData();

    }


    public LiveData<List<Measurement>> getMeasurementHistoryListLiveData(){
        return measurementRepository.getMeasurementHistory();
    }

}
