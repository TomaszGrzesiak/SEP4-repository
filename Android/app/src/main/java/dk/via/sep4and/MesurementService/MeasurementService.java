package dk.via.sep4and.MesurementService;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;

public interface MeasurementService {
    @GET("api/measurements")
    Call<ResponseBody> getMeasurements
            (@Query("id") int id,
             @Query("co2") double co2,
             @Query("humidity") double humidity,
             @Query("temperature") double temperature,
             @Query("timestamp") String timestamp);
}
