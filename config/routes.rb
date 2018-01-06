Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  namespace :api do
    namespace :v2 do
      resources :sensor_data
    end

    namespace :v1 do
      resources :sensor_data
    end
  end
end
