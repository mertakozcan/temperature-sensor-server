Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  root 'sensor_data#index'
  resources :sensor_data

  namespace :api do
    namespace :v1 do
      resources :sensor_data
    end
  end
end
