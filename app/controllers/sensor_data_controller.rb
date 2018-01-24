class SensorDataController < ApplicationController

  def index
    @sensor_data = SensorDatum.all
    @sorted_sensor_data = SensorDatum.order(created_at: :desc)
  end

end