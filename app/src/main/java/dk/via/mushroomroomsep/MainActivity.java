package dk.via.mushroomroomsep;

import android.os.Bundle;

import android.widget.Button;


import androidx.appcompat.app.AppCompatActivity;


import androidx.navigation.NavController;
import androidx.navigation.Navigation;




public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button buttonFragmentOne = findViewById(R.id.button_fragment_one);
        Button buttonFragmentTwo = findViewById(R.id.button_fragment_two);
        NavController navController = Navigation.findNavController(this, R.id.fragmentContainerView);



        buttonFragmentOne.setOnClickListener(v-> navController.navigate(R.id.measurementFragment));
        buttonFragmentTwo.setOnClickListener(v-> navController.navigate(R.id.fragmentInfoView));

    }
}


