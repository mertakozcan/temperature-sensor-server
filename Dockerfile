FROM ruby:2.5
RUN apt-get update -qq && apt-get install -y build-essential libpq-dev nodejs
RUN mkdir /temperature_app
WORKDIR /temperature_app
COPY Gemfile /temperature_app/Gemfile
COPY Gemfile.lock /temperature_app/Gemfile.lock
RUN bundle install
COPY . /temperature_app