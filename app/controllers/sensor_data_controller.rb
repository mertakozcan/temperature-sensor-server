class SensorDataController < ApplicationController

  def index
    @sensor_data = SensorDatum.order(created_at: :desc)

    respond_to do |format|
      format.html
      format.csv {
        date = request.query_parameters['date'] or Time.now.months_ago(1).strftime('%Y-%m')
        send_data SensorDatum.to_csv(date), filename: "sensor-#{date}.csv"
      }
    end
  end

end