package dk.via.mushroomroomsep;


import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

import androidx.lifecycle.ViewModelProvider;


import dk.via.mushroomroomsep.view.MeasurementFragmentViewModel;

import java.util.ArrayList;




public class MeasurementFragment extends Fragment {


    private TextView id;
    private TextView co2;
    private TextView humidity;
    private TextView lightLevel;
    private TextView temperature;
    private TextView timestamp;

    ListView lst;


    MeasurementFragmentViewModel measurementFragmentViewModel = new MeasurementFragmentViewModel();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        measurementFragmentViewModel = new ViewModelProvider(requireActivity()).get(MeasurementFragmentViewModel.class);


    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        return inflater.inflate(R.layout.measurement_fragment, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {



        measurementFragmentViewModel.getMeasurementHistoryListLiveData().observe(getViewLifecycleOwner(), measurements -> {


            measurements = measurementFragmentViewModel.getMeasurementHistoryListLiveData().getValue();




            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            lst = (ListView) view.findViewById(R.id.listView);
            ArrayList<String> listItems = new ArrayList<String>();


                listItems.add(String.valueOf(measurements.get(0).getId()));
                listItems.add(String.valueOf(measurements.get(0).getCo2()));
                listItems.add(String.valueOf(measurements.get(0).getHumidity()));
                listItems.add(String.valueOf(measurements.get(0).getLightLevel()));
                listItems.add(String.valueOf(measurements.get(0).getTemperature()));
                listItems.add(String.valueOf(measurements.get(0).getTimeStamp()));




            ArrayAdapter ad = new ArrayAdapter(getActivity(), android.R.layout.simple_list_item_1, listItems);

            lst.setAdapter(ad);



        });




    }












}
