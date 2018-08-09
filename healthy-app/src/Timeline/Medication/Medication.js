import React, {Component} from 'react';
import '../Timeline.css';


class Medication extends Component {
    constructor(props) {
        super(props);
        // console.log(props);
        this.even = true; //this.props.even;
    }

    render() {
        return (
            <div className={this.props.even ? "container left" : "container right"}>
                <div className="content">
                    <h5><i>Medication</i></h5>
                    <h2>{new Date(this.props.effectiveDateTime).toLocaleDateString()}</h2>
                    <p>{JSON.stringify(this.props.text)}</p>
                </div>
            </div>
        );
    }
}

export default Medication;