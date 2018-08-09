import React, {Component} from 'react';
import SearchInput from '../SearchInput/SearchInput';
import Patient from "../Patient/Patient";

class Search extends Component {
    constructor(props) {
        super(props);

        this.state = {
            isFetched: false
        };

        this.patients = [];
        this.handleSearchQuery = this.handleSearchQuery.bind(this);
        this.fetchPatients = this.fetchPatients.bind(this);
    }

    fetchPatients(name) {
        fetch(`http://hapi.fhir.org/baseDstu3/Patient?_format=json&name=` + name.toString())
            .then(blob => blob.json())
            .then(data => {
                this.patients = data.entry.map(element =>
                    <Patient
                        key={element.resource.id}
                        url={element.fullUrl}
                        name={element.resource.name.map(e => {
                            return e.text ? e.text : e.given[0] + " " + e.family;
                        })[0]}
                        id={element.resource.id}
                    />);

                this.setState({
                    isFetched: true,
                });
            })
            .catch(err => console.error(err));
    }

    handleSearchQuery(query) {
        this.setState({isFetched: false});
        this.fetchPatients(query)
    }

    render() {
        return (
            <div>
                <SearchInput onChange={this.handleSearchQuery}/>
                {this.patients}
            </div>

        );
    }
}

export default Search;