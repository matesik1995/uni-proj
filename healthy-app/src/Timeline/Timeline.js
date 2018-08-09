import React, {Component} from 'react';
import Observation from "./Observation/Observation";
import MedicationStatement from "./MedicationStatement/MedicationStatement";
import "react-month-picker-input/dist/react-month-picker-input.css";
import MonthPickerInput from 'react-month-picker-input';

class Timeline extends Component {
    constructor(props) {
        super(props);
        this.observations = this.props.items;
        this.state = {
            observations: this.props.items,
            medicationStatement: this.props.items
        };
    }

    handleFilter(maskedValue, selectedYear, selectedMonth, observations) {
        console.log(maskedValue);
        console.log(observations);
        if(observations) {
            this.setState({
                observations: observations
                    .filter(e => {
                        let d = new Date(e.resource.effectiveDateTime)
                        return d.getUTCMonth() === selectedMonth &&
                        d.getUTCFullYear() === selectedYear ? 1 : 0
                    })
            });
            this.forceUpdate();
        }
    }

    handleRemoveFilter(observations) {
        if(observations) {
            this.setState({
                observations: observations
            });
            this.forceUpdate();
        }
    }

    componentWillReceiveProps(nextProps) {
        console.log("prop items", nextProps.items);
        this.observations = nextProps.items
                .filter(e => e.resource.resourceType === 'Observation')
                .filter(e => e.resource.text ? 1 : 0)
                .sort((a, b) => {
                    return new Date(a.resource.effectiveDateTime) < new Date(b.resource.effectiveDateTime) ? 1 : -1           
                });
        this.setState({
            observations: this.observations,
            medicationStatement: nextProps.items
                .filter(e => e.resource.resourceType === 'MedicationStatement')
                .filter(e => e.resource.medicationCodeableConcept ? 1 : 0)
                .filter(e => e.resource.dosage ? 1 : 0)
                // .sort((a, b) => {
                //     return new Date(a.resource.effectiveDateTime) < new Date(b.resource.effectiveDateTime) ? 1 : -1
                // })
                .map((e, i) => {
                    return <MedicationStatement even={i % 2} {...(e.resource)}/>;
                })
        });
        this.forceUpdate();
    }

    render() {
        return (
            <div className="left">
                <h2>Observations timeline:</h2>
                <div className="timeline">
                    <div class="filter">
                        <span>Filter: </span>
                        <MonthPickerInput closeOnSelect='true' value={new Date()} onChange={(val, y, m) => {
                            this.handleFilter(val, y, m, this.observations)}}
                        />
                        <button onClick={e => {this.handleRemoveFilter(this.observations)}}>Remove filter</button>
                    </div>
                    {this.state.observations
                        .map((e, i) => {
                            return <Observation even={i % 2} {...(e.resource)}/>;
                        })
                    }
                </div>
                <h2>Medication statements:</h2>
                <div className="medicTable">{this.state.medicationStatement}</div>
            </div>
        );
    }
}

export default Timeline;