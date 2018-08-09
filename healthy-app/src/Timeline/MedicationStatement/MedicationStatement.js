import React, {Component} from 'react';
import '../Timeline.css';


class MedicationStatement extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className="content">
                <h5><i>MedicationStatement</i></h5>
                <h2>{this.props.medicationCodeableConcept.text}</h2>
                <p>{this.props.dosage[0].text}</p>
            </div>
        );
    }
}

export default MedicationStatement;