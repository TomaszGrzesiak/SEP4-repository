package dk.via.mushroomroomsep.adapter;


//public class MeasurementListAdapter extends RecyclerView.Adapter<MeasurementListAdapter.ViewHolder> {
//    private List<Measurement> measurements;
//
//    public MeasurementListAdapter(List<Measurement> measurements) {
//        this.measurements = measurements;
//
//
//    }
//
//    @Override
//    public MeasurementListAdapter.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
//        View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.card_row, viewGroup, false);
//        return new ViewHolder(view);
//    }
//
//    @Override
//    public void onBindViewHolder(ViewHolder holder, int i) {
//        holder.id.setText(String.valueOf(measurements.get(i).getId()));
//        holder.co2.setText(String.valueOf(measurements.get(i).getCo2()));
//        holder.humidity.setText(String.valueOf(measurements.get(i).getHumidity()));
//        holder.lightlevel.setText(String.valueOf(measurements.get(i).getLightLevel()));
//        holder.temperature.setText(String.valueOf(measurements.get(i).getTemperature()));
//        holder.timestamp.setText(String.valueOf(measurements.get(i).getTimeStamp()));
//    }
//
//    @Override
//    public int getItemCount() {
//        return measurements.size();
//    }
//
//    public static class ViewHolder extends RecyclerView.ViewHolder {
//        private TextView id, co2, humidity, lightlevel,temperature,timestamp;
//
//        public ViewHolder(View view) {
//            super(view);
//            id = (TextView) view.findViewById(R.id.measureId);
//            co2 = (TextView) view.findViewById(R.id.co2);
//            humidity = (TextView) view.findViewById(R.id.humidity);
//            lightlevel = (TextView) view.findViewById(R.id.lightLevel);
//            temperature = (TextView) view.findViewById(R.id.temperature);
//            timestamp = (TextView) view.findViewById(R.id.timestamp);
//        }
//    }
//}
