package dk.via.mushroomroomsep;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import dk.via.mushroomroomsep.view.InfoFragmentViewModel;




public class InfoFragment extends Fragment {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        InfoFragmentViewModel infoFragmentViewModel = new ViewModelProvider(requireActivity()).get(InfoFragmentViewModel.class);


    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        return inflater.inflate(R.layout.info_fragment, container, false);
    }
}
