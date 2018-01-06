Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  namespace :api do
    scope module: :v2, constraints: ApiConstraints.new(version: 2) do
      resources :sensor_data
    end

    scope module: :v1, constraints: ApiConstraints.new(version: 1, default: true) do
      resources :sensor_data
    end
  end
end
