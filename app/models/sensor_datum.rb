class SensorDatum < ApplicationRecord
  validates :temperature, :humidity, presence: true
end
