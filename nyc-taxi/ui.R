library(shinydashboard)
library(leaflet)
library(leaflet.extras)

dashboardPage(
    dashboardHeader(title = "New York City Taxi"),
    dashboardSidebar(
        sidebarMenu(
            menuItem("Introduction", tabName = "introduction"),
            menuItem("Map", tabName = "map"),
            menuItem("Target Value", tabName = "target-value"),
            menuItem("Date analysis", tabName = "date-analysis"),
            menuItem("More information", tabName = "more-information")
        )
    ),
    dashboardBody(
        tabItems(
            # First tab content
            tabItem(tabName = "introduction",
                    h2("Introduction"),
                    div("The competition dataset is based on the 2016 NYC Yellow Cab trip record data made available in Big Query on Google Cloud Platform. The data was originally published by the NYC Taxi and Limousine Commission (TLC). The data was sampled and cleaned for the purposes of this playground competition. Based on individual trip attributes, participants should predict the duration of each trip in the test set."),
                    h2("File descriptions"),
                    tags$ul(
                        tags$li("train.csv - the training set (contains 1458644 trip records)"),
                        tags$li("test.csv - the testing set (contains 625134 trip records)"),
                        tags$li("sample_submission.csv - a sample submission file in the correct format")
                    ),
                    h2("Data fields"),
                    tags$ul(
                        tags$li("id - a unique identifier for each trip"),
                        tags$li("vendor_id - a code indicating the provider associated with the trip record"),
                        tags$li("pickup_datetime - date and time when the meter was engaged"),
                        tags$li("dropoff_datetime - date and time when the meter was disengaged"),
                        tags$li("passenger_count - the number of passengers in the vehicle (driver entered value)"),
                        tags$li("pickup_longitude - the longitude where the meter was engaged"),
                        tags$li("pickup_latitude - the latitude where the meter was engaged"),
                        tags$li("dropoff_longitude - the longitude where the meter was disengaged"),
                        tags$li("dropoff_latitude - the latitude where the meter was disengaged"),
                        tags$li("store_and_fwd_flag - This flag indicates whether the trip record was held in vehicle memory before sending to the vendor because the vehicle did not have a connection to the server - Y=store and forward; N=not a store and forward trip"),
                        tags$li("trip_duration - duration of the trip in seconds")
                    )
            ),
            tabItem(tabName = "map",
                    box(
                        title = "Map",
                        width = 12, 
                        leafletOutput("mapPlot", height = 600)
                    )        
            ),
            tabItem(tabName = "target-value",
                    box(
                        title = "Target value",
                        width = 12,
                        plotOutput("targetPlot")
                    ),
                    box(
                        title = "Controls",
                        width = 12,
                        sliderInput("bins", "Number of observations:", 100, 1000, 500)
                    )
            ),
            tabItem(tabName = "date-analysis",
                    tabBox(
                        id = "datetabset", width = 12, 
                        tabPanel("Pickup date", 
                                 plotOutput("pickupDate"),
                                 box(
                                     title = "Date range",
                                     width = 6,
                                     dateInput("fromDate", "From:", value = "2012-02-29"),
                                     dateInput("toDate", "To:", value = "2020-02-29"),
                                 ),
                                 box(
                                     title = "Controls",
                                     width = 6,
                                     sliderInput("xxx", "Number of observations:", 1, 360, 31)
                                 )
                        ),
                        tabPanel("Arrival date", 
                                 plotOutput("arrivalDate")         
                        )
                    )
            ),
            tabItem(tabName = "more-information",
                    fluidRow(
                        box(
                            title = "Store and Forward Flag",
                            width = 6,
                            plotOutput("storeFwdFlag")
                        ),
                        box(
                            title = "Vendors",
                            width = 6,
                            plotOutput("vendors")
                        )
                    ),
                    fluidRow(
                        box(
                            title = "Passenger count",
                            width = 12,
                            plotOutput("passengerCount")
                        )
                    )          
            )
        )
    )
)
