library(shinydashboard)
library(ggplot2)
library(readr)
library(dplyr)
library(leaflet)
library(leaflet.extras)
library(maps)
library(lubridate)

train = read_csv("train.csv")
test = read_csv("test.csv")

train <- train %>%
    mutate(pickup_datetime = ymd_hms(pickup_datetime),
           dropoff_datetime = ymd_hms(dropoff_datetime),
           vendor_id = factor(vendor_id),
           passenger_count = factor(passenger_count))

shinyServer(function(input, output) {
    output$trainSummary <- renderPrint({
        summary(train)
    })
    
    output$testSummary <- renderPrint({
        summary(test)
    })
    
    output$targetPlot <- renderPlot({
        train %>%
            ggplot(aes(trip_duration)) +
            geom_histogram(fill = "#3c8dbc", bins = input$bins) +
            scale_x_log10() +
            scale_y_sqrt()
    })
    
    output$targetHead <- renderPrint({
        train %>%
            arrange(desc(trip_duration)) %>%
            select(trip_duration, pickup_datetime, dropoff_datetime, everything()) %>%
            head(10)
    })
    
    set.seed(1234)
    
    output$mapPlot <- renderLeaflet({
        
        foo <- sample_n(train, 1024)
        
        leaflet(data = foo) %>% addProviderTiles("Esri.NatGeoWorldMap") %>%
            addCircleMarkers(~ pickup_longitude, ~pickup_latitude, radius = 1,
                             color = "#3c8dbc", fillOpacity = 0.3)
    })
    
    output$pickupDateWhole <- renderPlot({
        train %>%
            ggplot(aes(pickup_datetime)) +
            geom_histogram(fill = "#3c8dbc", bins = input$pickupDateWholeBins) +
            labs(x = "Pickup dates")
    })
    
    
    output$pickupDateSelect <- renderPlot({
        train %>%
            filter(pickup_datetime > ymd(input$pickupDateFromDate) & pickup_datetime < ymd(input$pickupDateToDate)) %>%
            ggplot(aes(pickup_datetime)) +
            geom_histogram(fill = "#3c8dbc", bins = input$pickupDateSelectBins) +
            labs(x = "Narrowed pickup dates")
    })
    
    output$dropoffDateWhole <- renderPlot({
        train %>%
            ggplot(aes(dropoff_datetime)) +
            geom_histogram(fill = "#3c8dbc", bins = input$dropoffDateWholeBins) +
            labs(x = "Dropoff dates")
    })
    
    output$dropoffDateSelect <- renderPlot({
        train %>%
            filter(dropoff_datetime > ymd(input$dropoffDateFromDate) & dropoff_datetime < ymd(input$dropoffDateToDate)) %>%
            ggplot(aes(dropoff_datetime)) +
            geom_histogram(fill = "#3c8dbc", bins = input$dropoffDateSelectBins) +
            labs(x = "Narrowed dropoff dates")
    })
    
    output$storeFwdFlag <- renderPlot({
        train %>%
            ggplot(aes(store_and_fwd_flag)) +
            geom_bar(fill = "#3c8dbc") +
            theme(legend.position = "none") +
            scale_y_log10()
    })
    
    output$vendors <- renderPlot({
        train %>%
            ggplot(aes(vendor_id)) +
            geom_bar(fill = "#3c8dbc") +
            theme(legend.position = "none")
    })
    
    output$passengerCount <- renderPlot({
        train %>%
            group_by(passenger_count) %>%
            count() %>%
            ggplot(aes(passenger_count, n)) +
            geom_col(fill = "#3c8dbc") +
            scale_y_sqrt() +
            theme(legend.position = "none")
    })
    
    output$relation1_1 <- renderPlot({
        train %>%
            mutate(wday = wday(pickup_datetime, label = TRUE)) %>%
            group_by(wday, vendor_id) %>%
            summarise(median_duration = median(trip_duration)/60) %>%
            ggplot(aes(wday, median_duration, color = vendor_id)) +
            geom_point(size = 4) +
            labs(x = "Day of the week", y = "Median trip duration [min]")
    })
    output$relation1_2 <- renderPlot({
        train %>%
            mutate(hpick = hour(pickup_datetime)) %>%
            group_by(hpick, vendor_id) %>%
            summarise(median_duration = median(trip_duration)/60) %>%
            ggplot(aes(hpick, median_duration, color = vendor_id)) +
            geom_smooth(method = "loess", span = 1/2) +
            geom_point(size = 4) +
            labs(x = "Hour of the day", y = "Median trip duration [min]") +
            theme(legend.position = "none")
    })
})
