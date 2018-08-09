import React, {Component} from 'react';
import '../Timeline.css';


class Observation extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className={this.props.even ? "container left" : "container right"}>
                <div className="content">
                    <h5><i>Observation</i></h5>
                    <h2>{new Date(this.props.effectiveDateTime).toLocaleDateString()}</h2>
                    <p dangerouslySetInnerHTML={{__html: this.props.text.div}}/>
                </div>
            </div>
        );
    }
}

export default Observation;