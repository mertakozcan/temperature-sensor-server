module Api
  module V1
    class SensorDataController < ApplicationController
      def index
        @sensor_data = SensorDatum.all
        json_response(@sensor_data)
      end
    end
  end
end