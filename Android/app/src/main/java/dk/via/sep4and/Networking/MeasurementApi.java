package dk.via.sep4and.Networking;

import java.util.List;

import dk.via.sep4and.Model.Measurement;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Path;

public interface MeasurementApi {

    String route = "Measurement";


    @GET(route + "/{id}")
    Call<Measurement> getMeasurment(@Path("id") long measurmentId);
}
