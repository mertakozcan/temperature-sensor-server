class CreateSensorData < ActiveRecord::Migration[5.1]
  def change
    create_table :sensor_data do |t|
      t.float :temperature
      t.float :humidity

      t.timestamps
    end
  end
end
