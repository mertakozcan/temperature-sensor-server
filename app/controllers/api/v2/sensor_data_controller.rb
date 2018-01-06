module Api
  module V2
    class SensorDataController < ApplicationController
      def index
        json_response({ message: 'Hello, world'})
      end
    end
  end
end