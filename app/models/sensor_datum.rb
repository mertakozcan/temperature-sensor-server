require 'csv'

class SensorDatum < ApplicationRecord
  validates :temperature, :humidity, presence: true

  def self.to_csv(date)
    attributes = %w{Tarih Saat Sicaklik Nem}

    CSV.generate(headers: true) do |csv|
      csv << attributes

      date_obj = Date::strptime(date, "%Y-%m")
      all.where(:created_at => date_obj.beginning_of_month..date_obj.end_of_month).each do |datum|
        csv << [datum.created_at.in_time_zone('Istanbul').strftime('%d/%m/%y'),
                datum.created_at.in_time_zone('Istanbul').strftime('%H:%M'),
                datum.temperature,
                datum.humidity]
      end
    end
  end
end
