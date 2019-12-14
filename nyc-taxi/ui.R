library(shinydashboard)

library(leaflet)
library(leaflet.extras)

dashboardPage(
    dashboardHeader(title = "New York City Taxi"),
    dashboardSidebar(sidebarMenu(
        menuItem("Introduction", tabName = "introduction"),
        menuItem("Data overview",  tabName = "data-overview",
            menuSubItem("Overview", tabName = "data-overview"),
            menuSubItem("Target Value", tabName = "target-value"),
            menuSubItem("Map", tabName = "map"),
            menuSubItem("Date analysis", tabName = "date-analysis"),
            menuSubItem("More information", tabName = "more-information")
        ),
        menuItem("Data relations", tabName = "to-do",
            menuSubItem("Pickup date/time vs trip_duration", tabName = "relation1"),
            menuSubItem("Passenger count and Vendor vs trip_duration", tabName = "to-do"),
            menuSubItem("Store and Forward vs trip_duration", tabName = "to-do")
        )
    )), 
    dashboardBody(
        tabItems(
            # First tab content
            tabItem(
                tabName = "introduction",
                h2("Introduction"),
                div(
                    "The competition dataset is based on the 2016 NYC Yellow Cab trip record data made available in Big Query on Google Cloud Platform. The data was originally published by the NYC Taxi and Limousine Commission (TLC). The data was sampled and cleaned for the purposes of this playground competition. Based on individual trip attributes, participants should predict the duration of each trip in the test set."
                ),
                h2("File descriptions"),
                tags$ul(
                    tags$li("train.csv - the training set (contains 1458644 trip records)"),
                    tags$li("test.csv - the testing set (contains 625134 trip records)"),
                    tags$li(
                        "sample_submission.csv - a sample submission file in the correct format"
                    )
                ),
                h2("Data fields"),
                tags$ul(
                    tags$li("id - a unique identifier for each trip"),
                    tags$li(
                        "vendor_id - a code indicating the provider associated with the trip record"
                    ),
                    tags$li("pickup_datetime - date and time when the meter was engaged"),
                    tags$li("dropoff_datetime - date and time when the meter was disengaged"),
                    tags$li(
                        "passenger_count - the number of passengers in the vehicle (driver entered value)"
                    ),
                    tags$li("pickup_longitude - the longitude where the meter was engaged"),
                    tags$li("pickup_latitude - the latitude where the meter was engaged"),
                    tags$li("dropoff_longitude - the longitude where the meter was disengaged"),
                    tags$li("dropoff_latitude - the latitude where the meter was disengaged"),
                    tags$li(
                        "store_and_fwd_flag - This flag indicates whether the trip record was held in vehicle memory before sending to the vendor because the vehicle did not have a connection to the server - Y=store and forward; N=not a store and forward trip"
                    ),
                    tags$li("trip_duration - duration of the trip in seconds")
                )
            ),
            tabItem(
                tabName = "data-overview",
                h2("Data overview"),
                div(
                    "Training data consists of 11 variables. There are no nulls or missing values."
                ),
                verbatimTextOutput("trainSummary"),
                div(
                    "Test data consists of 9 variables. The trip_duration and dropoff_datetime fields are missing."
                ),
                verbatimTextOutput("testSummary")
            ),
            tabItem(
                tabName = "target-value",
                box(title = "Target value",
                    width = 12,
                    plotOutput("targetPlot")),
                box(
                    title = "Controls",
                    width = 12,
                    sliderInput("bins", "Number of bins:", 10, 200, 50)
                ),
                div(
                    "The majority of rides follow a rather smooth distribution that looks almost log-normal with a peak just short of 1000 seconds, i.e. about 17 minutes."
                ),
                div(
                    "Additionally, there is a strange delta-shaped peak of trip_duration just before the 1e5 seconds mark and even a few way above it"
                ),
                verbatimTextOutput("targetHead"),
                div(
                    "Those records would correspond to 24-hour trips and beyond, with a maximum of almost 12 days"
                )
            ),
            tabItem(
                tabName = "map",
                box(
                    title = "Map",
                    width = 12,
                    leafletOutput("mapPlot", height = 600)
                ),
                div(
                    "This map gives us a general overview of how the pickup and dropoff positions looks like."
                )
            ),
            
            tabItem(
                tabName = "date-analysis",
                tabBox(
                    id = "datetabset",
                    width = 12,
                    tabPanel(
                        "Pickup date",
                        plotOutput("pickupDateWhole"),
                        sliderInput("pickupDateWholeBins", "Number of bins:", 1, 360, 180),
                        plotOutput("pickupDateSelect"),
                        dateInput("pickupDateFromDate", "From:", value = "2016-01-20"),
                        dateInput("pickupDateToDate", "To:", value = "2016-02-05"),
                        sliderInput("pickupDateSelectBins", "Number of bins:", 1, 360, 180)
                    ),
                    tabPanel("Arrival date",
                         plotOutput("dropoffDateWhole"),
                         sliderInput("dropoffDateWholeBins", "Number of bins:", 1, 360, 180),
                         plotOutput("dropoffDateSelect"),
                         dateInput("dropoffDateFromDate", "From:", value = "2016-01-20"),
                         dateInput("dropoffDateToDate", "To:", value = "2016-02-05"),
                         sliderInput("dropoffDateSelectBins", "Number of bins:", 1, 360, 180)
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
                        box(title = "Vendors",
                            width = 6,
                            plotOutput("vendors"))
                    ),
                    fluidRow(
                        box(
                            title = "Passenger count",
                            width = 12,
                            plotOutput("passengerCount")
                        )
                    )
            ),
            tabItem(tabName = "relation1",
                    plotOutput("relation1_1"),
                    plotOutput("relation1_2"),
                    div("We find:

There is indeed a similar pattern as for the business of the day of the week. Vendor 2, the one with the more frequent trips, also has consistently higher trip durations than vendor 1. It will be worth adding the vendor_id feature to a model to test its predictive importance.

Over the course of a typical day we find a peak in the early afternoon and dips around 5-6am and 8pm. The weekday and hour of a trip appear to be important features for predicting its duration and should be included in a successful model.")
            ),
            tabItem(tabName = "to-do",
                    div("to do zrobionka")
            )
        )
    )
)
