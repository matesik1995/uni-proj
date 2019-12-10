library(shinydashboard)
library(ggplot2)
library(readr)
library(dplyr)
library(leaflet)
library(leaflet.extras)
library(maps)
library(lubridate)

train = read_csv("train.csv")
#test = read_csv("test.csv")

train <- train %>%
    mutate(pickup_datetime = ymd_hms(pickup_datetime),
           dropoff_datetime = ymd_hms(dropoff_datetime),
           vendor_id = factor(vendor_id),
           passenger_count = factor(passenger_count))

shinyServer(function(input, output) {
    set.seed(1234)
    
    output$mapPlot <- renderLeaflet({
        
        foo <- sample_n(train, 8e3)
        
        leaflet(data = foo) %>% addProviderTiles("Esri.NatGeoWorldMap") %>%
            addCircleMarkers(~ pickup_longitude, ~pickup_latitude, radius = 1,
                             color = "blue", fillOpacity = 0.3)
    })
    
    output$targetPlot <- renderPlot({
        train %>%
            ggplot(aes(trip_duration)) +
            geom_histogram(fill = "red", bins = input$bins) +
            scale_x_log10() +
            scale_y_sqrt()
    })
    
    output$pickupDate <- renderPlot({
        train %>%
            ggplot(aes(pickup_datetime)) +
            geom_histogram(fill = "red", bins = input$xxx) +
            labs(x = "Pickup dates")
    })
    
    output$arrivalDate <- renderPlot({
        train %>%
            ggplot(aes(dropoff_datetime)) +
            geom_histogram(fill = "blue", bins = 120) +
            labs(x = "Dropoff dates")
    })
    
    output$storeFwdFlag <- renderPlot({
        train %>%
            ggplot(aes(store_and_fwd_flag)) +
            geom_bar() +
            theme(legend.position = "none") +
            scale_y_log10()
    })
    
    output$vendors <- renderPlot({
        train %>%
            ggplot(aes(vendor_id, fill = vendor_id)) +
            geom_bar() +
            theme(legend.position = "none")
    })
    
    output$passengerCount <- renderPlot({
        train %>%
            group_by(passenger_count) %>%
            count() %>%
            ggplot(aes(passenger_count, n, fill = passenger_count)) +
            geom_col() +
            scale_y_sqrt() +
            theme(legend.position = "none")
    })
})
