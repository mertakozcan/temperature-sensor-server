class SensorDataController < ApplicationController

  def index
      @sensor_data = SensorDatum.all
  end

end