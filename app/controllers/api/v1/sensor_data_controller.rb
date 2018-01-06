module Api
  module V1
    class SensorDataController < ApplicationController
      before_action :set_sensor_datum, only: [:show]

      # GET /api/v1/sensor_data
      def index
        @sensor_data = SensorDatum.all
        json_response(@sensor_data)
      end

      # GET /api/v1/sensor_data/:id
      def show
        json_response(@sensor_datum)
      end

      # POST /api/v1/sensor_data
      def create
        @sensor_datum = SensorDatum.create!(sensor_datum_params)
        json_response(@sensor_datum, :created)
      end

      private
      def sensor_datum_params
        params.permit(:temperature, :humidity)
      end

      def set_sensor_datum
        @sensor_datum = SensorDatum.find(params[:id])
      end
    end
  end
end